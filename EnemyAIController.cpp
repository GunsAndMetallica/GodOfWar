#include "EnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "TimerManager.h"

AEnemyAIController::AEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = true;

    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 1200.f;
    SightConfig->LoseSightRadius = 1400.f;
    SightConfig->PeripheralVisionAngleDegrees = 70.f;
    SightConfig->SetMaxAge(5.f);
    SightConfig->DetectionByAffiliation.bDetectEnemies = true;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

    PerceptionComp->ConfigureSense(*SightConfig);
    PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    CurrentPatrolIndex = 0;

    if (PerceptionComp)
    {
        PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AEnemyAIController::OnPerceptionUpdated);
    }
}

void AEnemyAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    APawn* Controlled = GetPawn();
    if (!Controlled) return;

    // If no target, follow patrol
    if (PatrolPoints.Num() > 0 && !IsValid(PlayerPawn))
    {
        MoveToNextPatrolPoint();
    }
}

void AEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
    for (AActor* Actor : UpdatedActors)
    {
        if (!Actor) continue;

        // If player detected, engage
        APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
        if (Actor == Player)
        {
            EngageTarget(Actor);
            return;
        }
    }

    // If no player in updated list, start recheck timer
    GetWorldTimerManager().SetTimer(TimerHandle_RecheckTarget, this, &AEnemyAIController::RecheckTarget, 1.0f, false);
}

void AEnemyAIController::RecheckTarget()
{
    TArray<AActor*> Perceived;
    PerceptionComp->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(), Perceived);

    for (AActor* A : Perceived)
    {
        if (A == PlayerPawn) { EngageTarget(A); return; }
    }

    // No player perceived -> resume patrol
    Disengage();
}

void AEnemyAIController::MoveToNextPatrolPoint()
{
    if (PatrolPoints.Num() == 0) return;
    if (CurrentPatrolIndex >= PatrolPoints.Num()) CurrentPatrolIndex = 0;

    MoveToActor(PatrolPoints[CurrentPatrolIndex], PatrolAcceptanceRadius);
    CurrentPatrolIndex++;
}

void AEnemyAIController::EngageTarget(AActor* TargetActor)
{
    if (!TargetActor) return;
    StopMovement();

    // Move towards player and start attack behavior
    MoveToActor(TargetActor, 120.f);

    // Possessed pawn should be AEnemyCharacter (call TryAttack when in range)
    AEnemyCharacter* EnemyChar = Cast<AEnemyCharacter>(GetPawn());
    if (EnemyChar)
    {
        // Could bind a repeating timer that checks distance and calls TryAttack
        GetWorldTimerManager().SetTimer(TimerHandle_RecheckTarget, [this, EnemyChar, TargetActor]()
        {
            if (!EnemyChar || !TargetActor) return;

            float Distance = FVector::Dist(EnemyChar->GetActorLocation(), TargetActor->GetActorLocation());
            if (Distance <= EnemyChar->AttackRange + 50.f)
            {
                EnemyChar->TryAttack();
            }
            else
            {
                MoveToActor(TargetActor, 120.f);
            }
        }, 0.6f, true);
    }
}

void AEnemyAIController::Disengage()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_RecheckTarget);
    MoveToNextPatrolPoint();
}
