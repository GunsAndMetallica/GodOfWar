#include "BossAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

ABossAIController::ABossAIController() {
    PrimaryActorTick.bCanEverTick = true;
    Health = 500.f;
    Phase = 1;
}

void ABossAIController::BeginPlay() {
    Super::BeginPlay();
}

void ABossAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    BossAttack();
}

void ABossAIController::BossAttack() {
    // Attack patterns based on phase
    if(Phase == 1) { /* Light attacks */ }
    if(Phase == 2) { /* Heavy attacks + AoE */ }
    if(Phase == 3) { /* Rage mode + combo attacks */ }
}

void ABossAIController::ChangePhase() {
    if(Health <= 350.f && Phase == 1) Phase = 2;
    if(Health <= 150.f && Phase == 2) Phase = 3;
}

void ABossAIController::TakeDamage(float DamageAmount) {
    Health -= DamageAmount;
    ChangePhase();
    if(Health <= 0.f) {
        GetPawn()->Destroy(); // Boss defeated
    }
}
