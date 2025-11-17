#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "WeaponBase.h"

APlayerCharacter::APlayerCharacter() {
    PrimaryActorTick.bCanEverTick = true;
    Health = 100.f;
    MaxHealth = 100.f;
}

void APlayerCharacter::BeginPlay() {
    Super::BeginPlay();
}

void APlayerCharacter::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
    PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::JumpAction);
    PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &APlayerCharacter::Dodge);
    PlayerInputComponent->BindAction("AttackAxe", IE_Pressed, this, &APlayerCharacter::AttackAxe);
    PlayerInputComponent->BindAction("ThrowAxe", IE_Pressed, this, &APlayerCharacter::ThrowAxe);
    PlayerInputComponent->BindAction("RecallAxe", IE_Pressed, this, &APlayerCharacter::RecallAxe);
    PlayerInputComponent->BindAction("AttackBlades", IE_Pressed, this, &APlayerCharacter::AttackBlades);
    PlayerInputComponent->BindAction("Block", IE_Pressed, this, &APlayerCharacter::Block);
    PlayerInputComponent->BindAction("RageMode", IE_Pressed, this, &APlayerCharacter::RageMode);
}

void APlayerCharacter::MoveForward(float Value) { AddMovementInput(GetActorForwardVector(), Value); }
void APlayerCharacter::MoveRight(float Value) { AddMovementInput(GetActorRightVector(), Value); }
void APlayerCharacter::Turn(float Value) { AddControllerYawInput(Value); }
void APlayerCharacter::LookUp(float Value) { AddControllerPitchInput(Value); }
void APlayerCharacter::JumpAction() { Jump(); }
void APlayerCharacter::Dodge() { /* Add dodge animation + invulnerability */ }
void APlayerCharacter::AttackAxe() { /* Play axe attack animation + detect hit */ }
void APlayerCharacter::ThrowAxe() { /* Spawn axe projectile */ }
void APlayerCharacter::RecallAxe() { /* Move axe back to player */ }
void APlayerCharacter::AttackBlades() { /* Play dual blade combo */ }
void APlayerCharacter::Block() { /* Reduce damage */ }
void APlayerCharacter::RageMode() { /* Activate special attacks */ }
