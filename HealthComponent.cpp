#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"

UHealthComponent::UHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    MaxHealth = 100.f;
    CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentHealth = MaxHealth;
}

void UHealthComponent::ApplyDamage(float DamageAmount, AActor* DamageCauser)
{
    if (DamageAmount <= 0.f || CurrentHealth <= 0.f) return;

    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0.f, MaxHealth);
    float Delta = CurrentHealth - OldHealth;
    OnHealthChanged.Broadcast(this, Delta);

    if (CurrentHealth <= 0.f)
    {
        OnDeath.Broadcast(GetOwner());
        // optional: notify instigator via gameplay events
    }
}

void UHealthComponent::Heal(float HealAmount)
{
    if (HealAmount <= 0.f || CurrentHealth <= 0.f) return;
    float OldHealth = CurrentHealth;
    CurrentHealth = FMath::Clamp(CurrentHealth + HealAmount, 0.f, MaxHealth);
    float Delta = CurrentHealth - OldHealth;
    OnHealthChanged.Broadcast(this, Delta);
}
