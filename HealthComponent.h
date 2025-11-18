#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, UHealthComponent*, HealthComp, float, HealthDelta);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathSignature, AActor*, Victim);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODOFWAR6_API UHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UHealthComponent();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
    float MaxHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
    float CurrentHealth;

    UPROPERTY(BlueprintAssignable, Category="Events")
    FOnHealthChangedSignature OnHealthChanged;

    UPROPERTY(BlueprintAssignable, Category="Events")
    FOnDeathSignature OnDeath;

    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category="Health")
    void ApplyDamage(float DamageAmount, AActor* DamageCauser = nullptr);

    UFUNCTION(BlueprintCallable, Category="Health")
    void Heal(float HealAmount);
};
