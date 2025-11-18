#include "EnemyCharacter.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Animation/AnimInstance.h"
#include "DrawDebugHelpers.h"

AEnemyCharacter::AEnemyCharacter()
{
    PrimaryActorTick.bCanEverTick = true;
    HealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComp"));
    MeleeDamage = 20.f;
    AttackRange = 150.f;
    AttackCooldown = 1.2f;
    bCanAttack = true;
    CurrentState = EEnemyState::Idle;
    bIsDead = false;

    // Optional: set collision channels, movement settings
    GetCharacterMovement()->MaxWalkSpeed = 300.f;
}

void AEnemyCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (HealthComp)
    {
        HealthComp->OnHealthChanged.AddDynamic(this, &AEnemyCharacter::OnTakeDamage);
        HealthComp->OnDeath.AddDynamic(this, &AEnemyCharacter::OnDeath);
    }
}

void AEnemyCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    // Optionally update state / do patrol logic here if not using AIController
}

void AEnemyCharacter::TryAttack()
{
    if (!bCanAttack || bIsDead) return;

    bCanAttack = false;

    // Play attack montage
    if (AttackMontage)
    {
        UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
        if (AnimInst)
        {
            AnimInst->Montage_Play(AttackMontage);
            // You should place an AnimNotify in the montage to call PerformMeleeTrace at the right frame.
            // Alternatively call PerformMeleeTrace after a short delay:
            FTimerHandle Temp;
            GetWorldTimerManager().SetTimer(Temp, this, &AEnemyCharacter::PerformMeleeTrace, 0.35f, false);
        }
    }
    else
    {
        // If no montage present, do an immediate trace
        PerformMeleeTrace();
    }

    // Set cooldown
    GetWorldTimerManager().SetTimer(TimerHandle_AttackCooldown, this, &AEnemyCharacter::ResetAttack, AttackCooldown, false);
}

void AEnemyCharacter::PerformMeleeTrace()
{
    if (bIsDead) return;

    FVector Start = GetActorLocation() + FVector(0.f, 0.f, 50.f);
    FVector Forward = GetActorForwardVector();
    FVector End = Start + (Forward * AttackRange);

    FCollisionShape Shape = FCollisionShape::MakeSphere(75.f);
    TArray<FHitResult> HitResults;
    FCollisionQueryParams Params;
    Params.AddIgnoredActor(this);

    bool bHit = GetWorld()->SweepMultiByChannel(HitResults, Start, End, FQuat::Identity, ECC_Pawn, Shape, Params);

    for (auto& Hit : HitResults)
    {
        AActor* HitActor = Hit.GetActor();
        if (HitActor)
        {
            // Attempt to apply damage via HealthComponent if present
            UHealthComponent* OtherHealth = HitActor->FindComponentByClass<UHealthComponent>();
            if (OtherHealth)
            {
                OtherHealth->ApplyDamage(MeleeDamage, this);
            }
            else
            {
                // Fallback: standard damage
                UGameplayStatics::ApplyDamage(HitActor, MeleeDamage, GetController(), this, nullptr);
            }
        }
    }

    // debug
    DrawDebugSphere(GetWorld(), End, 75.f, 12, FColor::Red, false, 1.0f);
}

void AEnemyCharacter::ResetAttack()
{
    bCanAttack = true;
}

void AEnemyCharacter::OnTakeDamage(UHealthComponent* OwningComp, float DamageDelta)
{
    // Play hit react animation or flinch
    if (bIsDead) return;

    // Optional: play stun, change state to Alerted
    CurrentState = EEnemyState::Alerted;

    // small invulnerability or stagger logic could be added here
}

void AEnemyCharacter::OnDeath(AActor* Victim)
{
    if (bIsDead) return;
    bIsDead = true;
    CurrentState = EEnemyState::Dead;

    // Stop movement
    GetCharacterMovement()->DisableMovement();

    // Play death anim (if exists)
    UAnimInstance* AnimInst = GetMesh()->GetAnimInstance();
    if (AnimInst)
    {
        // assume you have a death montage or anim
        // AnimInst->Montage_Play(DeathMontage)
    }

    // Disable collision and schedule destroy
    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    SetLifeSpan(8.f);
}
