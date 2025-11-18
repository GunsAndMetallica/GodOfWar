#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

class UHealthComponent;
class UAnimMontage;
class UBoxComponent;

UENUM(BlueprintType)
enum class EEnemyState : uint8
{
    Idle,
    Patrolling,
    Alerted,
    Combat,
    Dead
};

UCLASS()
class GODOFWAR6_API AEnemyCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    AEnemyCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UHealthComponent* HealthComp;

    // Attack
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    float MeleeDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    float AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    float AttackCooldown;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    UAnimMontage* AttackMontage;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
    bool bCanAttack;

    UFUNCTION(BlueprintCallable, Category="Combat")
    void TryAttack();

    UFUNCTION(BlueprintCallable)
    void PerformMeleeTrace(); // called from AnimNotify or timer

    UFUNCTION()
    void OnTakeDamage(UHealthComponent* OwningComp, float DamageDelta);

    UFUNCTION()
    void OnDeath(AActor* Victim);

    // States
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="State")
    EEnemyState CurrentState;

protected:
    FTimerHandle TimerHandle_AttackCooldown;
    void ResetAttack();

    // Utility
    bool bIsDead;
};
