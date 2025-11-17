#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

UCLASS()
class GODOFWAR6_API AWeaponBase : public AActor
{
    GENERATED_BODY()
public: 
    AWeaponBase();
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float AttackSpeed;

    void Attack();
};
