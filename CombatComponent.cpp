#include "CombatComponent.h"
#include "WeaponBase.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"

UCombatComponent::UCombatComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    bBlocking = false;
}

void UCombatComponent::BeginPlay()
{
    Super::BeginPlay();
    OwnerActor = GetOwner();
}

void UCombatComponent::PrimaryAttack()
{
    if (!OwnerActor) return;
    ACharacter* Char = Cast<ACharacter>(OwnerActor);
    if (!Char) return;
    if (AxeAttackMontage)
    {
        Char->PlayAnimMontage(AxeAttackMontage);
        // schedule DoMeleeTrace at specific time via timer or anim notify
        FTimerHandle Th;
        GetWorld()->GetTimerManager().SetTimer(Th, [this]() { DoMeleeTrace(EquippedAxe ? EquippedAxe->Damage : 25.f); }, 0.35f, false);
    }
    else DoMeleeTrace(EquippedAxe ? EquippedAxe->Damage : 25.f);
}

void UCombatComponent::SecondaryAttack()
{
    if (!OwnerActor) return;
    ACharacter* Char = Cast<ACharacter>(OwnerActor);
    if (!Char) return;
    if (BladesAttackMontage)
    {
        Char->PlayAnimMontage(BladesAttackMontage);
        FTimerHandle Th;
        GetWorld()->GetTimerManager().SetTimer(Th, [this]() { DoMeleeTrace(EquippedBlades ? EquippedBlades->Damage : 15.f); }, 0.25f, false);
    }
    else DoMeleeTrace(EquippedBlades ? EquippedBlades->Damage : 15.f);
}

void UCombatComponent::ThrowWeapon()
{
    // spawn projectile actor from weapon and simulate physics; detach weapon
    if(EquippedAxe) EquippedAxe->OnThrown();
}

void UCombatComponent::RecallWeapon()
{
    if(EquippedAxe) EquippedAxe->OnRecall();
}

void UCombatComponent::StartBlock() { bBlocking = true; }
void UCombatComponent::StopBlock() { bBlocking = false; }

void UCombatComponent::DoMeleeTrace(float Damage)
{
    if (!OwnerActor) return;

    FVector Start = OwnerActor->GetActorLocation() + FVector(0,0,50);
    FVector Forward = OwnerActor->GetActorForwardVector();
    FVector End = Start + Forward * 200.f;
    FCollisionShape Sphere = FCollisionShape::MakeSphere(90.f);
    TArray<FHitResult> Hits;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(OwnerActor);

    bool bHit = GetWorld()->SweepMultiByChannel(Hits, Start, End, FQuat::Identity, ECC_Pawn, Sphere, Params);
    for (auto& H : Hits)
    {
        if (AActor* HitActor = H.GetActor())
        {
            UHealthComponent* Health = HitActor->FindComponentByClass<UHealthComponent>();
            if (Health)
            {
                Health->ApplyDamage(Damage, OwnerActor);
            }
            else
            {
                UGameplayStatics::ApplyDamage(HitActor, Damage, nullptr, OwnerActor, nullptr);
            }
        }
    }

    DrawDebugSphere(GetWorld(), End, 90.f, 10, FColor::Orange, false, 0.6f);
}
