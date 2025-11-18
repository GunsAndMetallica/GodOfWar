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

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Boss")
    float Health = 1000.f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Boss")
    int32 Phase; // 1,2,3

protected:
    virtual void BeginPlay() override;

    void BossBehaviorTick();
    FTimerHandle Timer_Behavior;

    void EnterPhase(int32 NewPhase);
    void DoPhase1();
    void DoPhase2();
    void DoPhase3();

    void CheckTransitions();
};
