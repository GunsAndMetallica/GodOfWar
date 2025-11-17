#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class GODOFWAR6_API AEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AEnemyAIController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    class APawn* PlayerPawn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float Health;

    void Patrol();
    void DetectPlayer();
    void AttackPlayer();
    void TakeDamage(float DamageAmount);
};

