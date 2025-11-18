#include "RangedProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "HealthComponent.h"

ARangedProjectile::ARangedProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    RootComponent = Mesh;
    Mesh->SetSimulatePhysics(false);
    Mesh->SetCollisionProfileName("Projectile");

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjMove"));
    ProjectileMovement->InitialSpeed = 1400.f;
    ProjectileMovement->MaxSpeed = 1400.f;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    InitialLifeSpan = 6.f;

    Mesh->OnComponentHit.AddDynamic(this, &ARangedProjectile::OnHit);
}

void ARangedProjectile::BeginPlay()
{
    Super::BeginPlay();
}

void ARangedProjectile::FireInDirection(const FVector& ShootDirection)
{
    if (ProjectileMovement)
    {
        ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
    }
}

void ARangedProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
                              UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (OtherActor && OtherActor != this && OtherComp)
    {
        UHealthComponent* HC = OtherActor->FindComponentByClass<UHealthComponent>();
        if (HC)
        {
            HC->ApplyDamage(Damage, GetInstigator());
        }
        else
        {
            UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
        }
    }
    Destroy();
}
