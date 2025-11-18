#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatComponent.generated.h"

class AWeaponBase;
class UAnimMontage;
class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODOFWAR6_API UCombatComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCombatComponent();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
    AWeaponBase* EquippedAxe;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons")
    AWeaponBase* EquippedBlades;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    UAnimMontage* AxeAttackMontage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
    UAnimMontage* BladesAttackMontage;

    UFUNCTION(BlueprintCallable)
    void PrimaryAttack();

    UFUNCTION(BlueprintCallable)
    void SecondaryAttack();

    UFUNCTION(BlueprintCallable)
    void ThrowWeapon();

    UFUNCTION(BlueprintCallable)
    void RecallWeapon();

    UFUNCTION(BlueprintCallable)
    void StartBlock();

    UFUNCTION(BlueprintCallable)
    void StopBlock();

protected:
    AActor* OwnerActor;
    bool bBlocking;
    void DoMeleeTrace(float Damage);
};
