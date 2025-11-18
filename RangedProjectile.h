#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RangedProjectile.generated.h"

UCLASS()
class GODOFWAR6_API ARangedProjectile : public AActor
{
    GENERATED_BODY()
public:
    ARangedProjectile();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UProjectileMovementComponent* ProjectileMovement;

    UPROPERTY(VisibleAnywhere)
    class UStaticMeshComponent* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage = 35.f;

    void FireInDirection(const FVector& ShootDirection);

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
               FVector NormalImpulse, const FHitResult& Hit);
};
