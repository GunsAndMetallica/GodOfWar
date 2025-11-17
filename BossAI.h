#pragma once
#include "CoreMinimal.h"
#include "AIController.h"
#include "BossAIController.generated.h"

UCLASS()
class GODOFWAR6_API ABossAIController : public AAIController
{
    GENERATED_BODY()

public:
    ABossAIController();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
    float Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
    int Phase; // 1, 2, 3

    void BossAttack();
    void ChangePhase();
    void TakeDamage(float DamageAmount);
};
