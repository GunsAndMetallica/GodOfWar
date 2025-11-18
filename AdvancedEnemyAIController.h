#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "AdvancedEnemyAIController.generated.h"

UENUM(BlueprintType)
enum class EEnemyRole : uint8
{
    Grunt       UMETA(DisplayName="Grunt"),
    Elite       UMETA(DisplayName="Elite"),
    Ranged      UMETA(DisplayName="Ranged")
};

UCLASS()
class GODOFWAR6_API AAdvancedEnemyAIController : public AAIController
{
    GENERATED_BODY()

public:
    AAdvancedEnemyAIController();

    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaSeconds) override;

    /* Perception */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
    class UAIPerceptionComponent* PerceptionComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AI")
    class UAISenseConfig_Sight* SightConfig;

    /* Role */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    EEnemyRole Role = EEnemyRole::Grunt;

    /* Combat params */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float AttackRange = 200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float RangedMinRange = 500.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float RangedMaxRange = 1200.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TArray<AActor*> PatrolPoints;

    /* Patrol */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float PatrolAcceptanceRadius = 80.f;

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnPerceptionUpdated(const TArray<AActor*>& UpdatedActors);

    void MoveToNextPatrolPoint();
    int32 CurrentPatrolIndex;
    APawn* PlayerPawn;

    /* Combat loop */
    FTimerHandle Timer_HandleCombatTick;
    void CombatTick();

    /* Helpers */
    void EngageTarget(AActor* TargetActor);
    void Disengage();
    bool IsPlayerInAttackRange() const;
    bool IsPlayerVisible() const;

    /* Ranged */
    UPROPERTY(EditDefaultsOnly, Category="Ranged")
    TSubclassOf<class ARangedProjectile> RangedProjectileClass;

    void DoRangedAttack();

    /* Elite behaviors */
    void TryFlank();
};
