#include "EnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

AEnemyAIController::AEnemyAIController() {
    PrimaryActorTick.bCanEverTick = true;
    AttackRange = 200.f;
    Health = 100.f;
}

void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void AEnemyAIController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    DetectPlayer();
}

void AEnemyAIController::Patrol() {
    // Add waypoint movement logic
}

void AEnemyAIController::DetectPlayer() {
    if(!PlayerPawn) return;

    float Distance = FVector::Dist(GetPawn()->GetActorLocation(), PlayerPawn->GetActorLocation());
    if(Distance <= AttackRange) {
        AttackPlayer();
    } else {
        Patrol();
    }
}

void AEnemyAIController::AttackPlayer() {
    // Play attack animation & apply damage to player
}

void AEnemyAIController::TakeDamage(float DamageAmount) {
    Health -= DamageAmount;
    if(Health <= 0.f) {
        GetPawn()->Destroy();
    }
}
