#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CombatComponent.h"
#include "RageMode.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

APlayerCharacter::APlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    /* -------- CAMERA SETUP -------- */
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArm->SetupAttachment(RootComponent);
    SpringArm->TargetArmLength = 350.f;           // Over-shoulder distance
    SpringArm->bUsePawnControlRotation = true;
    SpringArm->SocketOffset = FVector(0.f, 60.f, 60.f);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
    Camera->bUsePawnControlRotation = false;

    /* -------- MOVEMENT SETTINGS -------- */
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.35f;

    /* -------- COMBAT + RAGE -------- */
    CombatComp = CreateDefaultSubobject<UCombatComponent>(TEXT("CombatComponent"));
    RageComp = CreateDefaultSubobject<URageMode>(TEXT("RageComponent"));
}

void APlayerCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    /* -------- MOVEMENT -------- */
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);
    PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &APlayerCharacter::Dodge);

    /* -------- COMBAT -------- */
    PlayerInputComponent->BindAction("LightAttack", IE_Pressed, this, &APlayerCharacter::LightAttack);
    PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &APlayerCharacter::HeavyAttack);
    PlayerInputComponent->BindAction("ThrowWeapon", IE_Pressed, this, &APlayerCharacter::ThrowWeapon);
    PlayerInputComponent->BindAction("RecallWeapon", IE_Pressed, this, &APlayerCharacter::RecallWeapon);

    PlayerInputComponent->BindAction("Block", IE_Pressed, this, &APlayerCharacter::BlockPressed);
    PlayerInputComponent->BindAction("Block", IE_Released, this, &APlayerCharacter::BlockReleased);

    PlayerInputComponent->BindAction("Rage", IE_Pressed, this, &APlayerCharacter::ActivateRage);
}

/* ========================================================
   MOVEMENT
======================================================== */

void APlayerCharacter::MoveForward(float Value)
{
    if (Value != 0.f)
        AddMovementInput(GetActorForwardVector(), Value);
}

void APlayerCharacter::MoveRight(float Value)
{
    if (Value != 0.f)
        AddMovementInput(GetActorRightVector(), Value);
}

void APlayerCharacter::Turn(float Value)
{
    AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::StartJump()
{
    Jump();
}

void APlayerCharacter::StopJump()
{
    StopJumping();
}

void APlayerCharacter::Dodge()
{
    if (!CombatComp) return;
    CombatComp->Dodge();
}

/* ========================================================
   COMBAT
======================================================== */

void APlayerCharacter::LightAttack()
{
    if (!CombatComp) return;
    CombatComp->PerformLightAttack();
}

void APlayerCharacter::HeavyAttack()
{
    if (!CombatComp) return;
    CombatComp->PerformHeavyAttack();
}

void APlayerCharacter::ThrowWeapon()
{
    if (!CombatComp) return;
    CombatComp->ThrowWeapon();
}

void APlayerCharacter::RecallWeapon()
{
    if (!CombatComp) return;
    CombatComp->RecallWeapon();
}

void APlayerCharacter::BlockPressed()
{
    if (!CombatComp) return;
    CombatComp->StartBlocking();
}

void APlayerCharacter::BlockReleased()
{
    if (!CombatComp) return;
    CombatComp->StopBlocking();
}

void APlayerCharacter::ActivateRage()
{
    if (!RageComp) return;
    RageComp->ActivateRageMode();
}

