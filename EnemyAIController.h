#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GODOFWAR6_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AEnemyAIController();

    virtual void Tick(float DeltaTime) override;
    virtual void OnPossess(APawn* InPawn) override;

    // Perception
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
    class UAIPerceptionComponent* PerceptionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
    class UAISenseConfig_Sight* SightConfig;

    UFUNCTION()
    void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

    // Simple Behavior
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float PatrolAcceptanceRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TArray<AActor*> PatrolPoints;

protected:
    APawn* PlayerPawn;
    int32 CurrentPatrolIndex;
    void MoveToNextPatrolPoint();

    // Combat helpers
    void EngageTarget(AActor* TargetActor);
    void Disengage();

    FTimerHandle TimerHandle_RecheckTarget;
    void RecheckTarget();
};
