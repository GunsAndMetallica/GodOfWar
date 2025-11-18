#include "AdvancedEnemyAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyCharacter.h"
#include "NavigationSystem.h"
#include "TimerManager.h"
#include "RangedProjectile.h"

AAdvancedEnemyAIController::AAdvancedEnemyAIController()
{
    PrimaryActorTick.bCanEverTick = true;

    PerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComp"));
    SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightConfig"));

    SightConfig->SightRadius = 1400.f;
    SightConfig->LoseSightRadius = 1600.f;
    SightConfig->PeripheralVisionAngleDegrees = 70.f;
    SightConfig->DetectionByAffiliation.bDetectEnemies = false;
    SightConfig->DetectionByAffiliation.bDetectFriendlies = false;
    SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

    PerceptionComp->ConfigureSense(*SightConfig);
    PerceptionComp->SetDominantSense(SightConfig->GetSenseImplementation());
}

void AAdvancedEnemyAIController::BeginPlay()
{
    Super::BeginPlay();
    CurrentPatrolIndex = 0;
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PerceptionComp)
        PerceptionComp->OnPerceptionUpdated.AddDynamic(this, &AAdvancedEnemyAIController::OnPerceptionUpdated);
}

void AAdvancedEnemyAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void AAdvancedEnemyAIController::OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors)
{
    for (AActor* Actor : UpdatedActors)
    {
        if (!Actor) continue;
        if (Actor == PlayerPawn)
        {
            EngageTarget(Actor);
            return;
        }
    }
    // fallback: no player in updated list -> recheck after a short time
    GetWorldTimerManager().SetTimer(Timer_HandleCombatTick, this, &AAdvancedEnemyAIController::CombatTick, 0.35f, false);
}

void AAdvancedEnemyAIController::BeginPlay() {} // redundant safe placeholder

void AAdvancedEnemyAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* ControlledPawn = GetPawn();
    if (!ControlledPawn) return;

    // If we have no visible player, patrol
    if (!IsPlayerVisible())
    {
        if (PatrolPoints.Num() > 0)
            MoveToNextPatrolPoint();
    }
}

void AAdvancedEnemyAIController::MoveToNextPatrolPoint()
{
    if (PatrolPoints.Num() == 0) return;
    if (CurrentPatrolIndex >= PatrolPoints.Num()) CurrentPatrolIndex = 0;

    MoveToActor(PatrolPoints[CurrentPatrolIndex], PatrolAcceptanceRadius);
    CurrentPatrolIndex++;
}

void AAdvancedEnemyAIController::EngageTarget(AActor* TargetActor)
{
    if (!TargetActor) return;
    StopMovement();

    // start combat tick loop
    GetWorldTimerManager().ClearTimer(Timer_HandleCombatTick);
    GetWorldTimerManager().SetTimer(Timer_HandleCombatTick, this, &AAdvancedEnemyAIController::CombatTick, 0.45f, true, 0.1f);
}

void AAdvancedEnemyAIController::Disengage()
{
    GetWorldTimerManager().ClearTimer(Timer_HandleCombatTick);
    MoveToNextPatrolPoint();
}

bool AAdvancedEnemyAIController::IsPlayerVisible() const
{
    if (!PerceptionComp || !PlayerPawn) return false;
    TArray<AActor*> Perceived;
    PerceptionComp->GetCurrentlyPerceivedActors(SightConfig->GetSenseImplementation(), Perceived);
    return Perceived.Contains(PlayerPawn);
}

bool AAdvancedEnemyAIController::IsPlayerInAttackRange() const
{
    APawn* P = PlayerPawn;
    APawn* Controlled = GetPawn();
    if (!P || !Controlled) return false;
    float Dist = FVector::Dist(P->GetActorLocation(), Controlled->GetActorLocation());
    return Dist <= AttackRange + 50.f;
}

void AAdvancedEnemyAIController::CombatTick()
{
    APawn* Controlled = GetPawn();
    if (!Controlled || !PlayerPawn) return;

    float Dist = FVector::Dist(Controlled->GetActorLocation(), PlayerPawn->GetActorLocation());

    // Ranged-specific behaviour
    if (Role == EEnemyRole::Ranged)
    {
        if (Dist > RangedMaxRange)
        {
            MoveToActor(PlayerPawn, RangedMaxRange - 100.f); // approach
        }
        else if (Dist < RangedMinRange)
        {
            // retreat slightly
            UNavigationSystemV1* Nav = UNavigationSystemV1::GetCurrent(GetWorld());
            if (Nav)
            {
                FVector Away = Controlled->GetActorLocation() + (Controlled->GetActorLocation() - PlayerPawn->GetActorLocation()).GetSafeNormal() * 400.f;
                FNavLocation Loc;
                if (Nav->GetRandomPointInNavigableRadius(Away, 150.f, Loc))
                    MoveToLocation(Loc.Location);
            }
        }
        else
        {
            StopMovement();
            DoRangedAttack();
        }
        return;
    }

    // Melee behaviours (Grunt / Elite)
    if (Dist <= AttackRange + 40.f)
    {
        // In range -> attack
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Controlled);
        if (Enemy)
        {
            // Elite has higher chance for heavy attack / dodge
            if (Role == EEnemyRole::Elite)
            {
                // randomize behavior
                float R = FMath::FRand();
                if (R < 0.2f) Enemy->TryDodge();          // roll/dodge
                else if (R < 0.5f) Enemy->TryHeavyAttack();
                else Enemy->TryAttack();
                // occasional flank
                if (FMath::FRand() < 0.15f) TryFlank();
            }
            else // grunt
            {
                Enemy->TryAttack();
            }
        }
    }
    else
    {
        // not in range -> move closer
        MoveToActor(PlayerPawn, AttackRange - 20.f);
    }
}

void AAdvancedEnemyAIController::DoRangedAttack()
{
    APawn* Controlled = GetPawn();
    if (!Controlled || !PlayerPawn) return;
    if (!RangedProjectileClass) return;

    FVector Muzzle = Controlled->GetActorLocation() + FVector(0,0,80.f);
    FActorSpawnParameters Params;
    Params.Instigator = Cast<APawn>(Controlled);
    ARangedProjectile* Proj = GetWorld()->SpawnActor<ARangedProjectile>(RangedProjectileClass, Muzzle, (PlayerPawn->GetActorLocation()-Muzzle).Rotation(), Params);
    if (Proj)
    {
        FVector Dir = (PlayerPawn->GetActorLocation() + FVector(0,0,60.f) - Muzzle).GetSafeNormal();
        Proj->FireInDirection(Dir);
    }
}

void AAdvancedEnemyAIController::TryFlank()
{
    APawn* Controlled = GetPawn();
    if (!Controlled || !PlayerPawn) return;
    UNavigationSystemV1* Nav = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!Nav) return;

    // pick a lateral point near player to flank to
    FVector PlayerLoc = PlayerPawn->GetActorLocation();
    FVector Right = (PlayerPawn->GetActorRightVector() * (FMath::FRandRange(1, 1.5f) * (FMath::RandBool() ? 1 : -1) * 300.f));
    FVector Target = PlayerLoc + Right + PlayerPawn->GetActorForwardVector() * FMath::FRandRange(-200.f, 200.f);

    FNavLocation NavLoc;
    if (Nav->GetRandomPointInNavigableRadius(Target, 120.f, NavLoc))
    {
        MoveToLocation(NavLoc.Location);
    }
}
