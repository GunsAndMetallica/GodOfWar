#include "BossAIController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "EnemyCharacter.h"
#include "NavigationSystem.h"

ABossAIController::ABossAIController()
{
    PrimaryActorTick.bCanEverTick = true;
    Phase = 1;
    Health = 1500.f;
}

void ABossAIController::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(Timer_Behavior, this, &ABossAIController::BossBehaviorTick, 0.7f, true, 0.2f);
}

void ABossAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

void ABossAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    CheckTransitions();
}

void ABossAIController::BossBehaviorTick()
{
    APawn* BossPawn = GetPawn();
    APawn* Player = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (!BossPawn || !Player) return;

    switch (Phase)
    {
        case 1: DoPhase1(); break;
        case 2: DoPhase2(); break;
        case 3: DoPhase3(); break;
        default: DoPhase1(); break;
    }
}

void ABossAIController::EnterPhase(int32 NewPhase)
{
    Phase = NewPhase;
    // play phase-change VFX / invulnerability window via BP events
}

void ABossAIController::DoPhase1()
{
    // aggressive melee combos and tracking
    AEnemyCharacter* BossChar = Cast<AEnemyCharacter>(GetPawn());
    if (BossChar)
    {
        BossChar->TryAttack();
    }
}

void ABossAIController::DoPhase2()
{
    // heavy AoE attacks or slam; occasionally dash
    AEnemyCharacter* BossChar = Cast<AEnemyCharacter>(GetPawn());
    if (BossChar)
    {
        // heavy attack every tick with chance
        if (FMath::FRand() < 0.4f) BossChar->TryHeavyAttack();
        else BossChar->TryAttack();
    }
}

void ABossAIController::DoPhase3()
{
    // enraged: faster combos + ground slam + special telegraphed unblockables
    AEnemyCharacter* BossChar = Cast<AEnemyCharacter>(GetPawn());
    if (BossChar)
    {
        if (FMath::FRand() < 0.6f) BossChar->TryHeavyAttack();
        if (FMath::FRand() < 0.2f) BossChar->TrySpecialSlam(); // implement in EnemyCharacter
    }
}

void ABossAIController::CheckTransitions()
{
    // assumes BossPawn has HealthComponent
    APawn* BossPawn = GetPawn();
    if (!BossPawn) return;

    UHealthComponent* HC = BossPawn->FindComponentByClass<UHealthComponent>();
    if (!HC) return;

    float Current = HC->CurrentHealth;
    float Max = HC->MaxHealth;

    if (Phase == 1 && Current <= Max * 0.66f)
    {
        EnterPhase(2);
    }
    else if (Phase == 2 && Current <= Max * 0.33f)
    {
        EnterPhase(3);
    }
}
