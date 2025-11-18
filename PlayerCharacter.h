#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CombatComponent.h"
#include "RageMode.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GODOFWAR6_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APlayerCharacter();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    /* ------------------ MOVEMENT ------------------ */
    void MoveForward(float Value);
    void MoveRight(float Value);
    void Turn(float Value);
    void LookUp(float Value);
    void StartJump();
    void StopJump();
    void Dodge();

    /* ------------------ COMBAT ------------------ */
    void LightAttack();        // Primary attack
    void HeavyAttack();        // Secondary attack
    void ThrowWeapon();
    void RecallWeapon();
    void BlockPressed();
    void BlockReleased();
    void ActivateRage();

    /* ------------------ COMPONENTS ------------------ */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    class USpringArmComponent* SpringArm;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    class UCameraComponent* Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
    UCombatComponent* CombatComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Rage")
    URageMode* RageComp;

    /* ------------------ STATS ------------------ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
    float Health = 100.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
    float MaxHealth = 100.f;

    /* ------------------ CAMERA SETTINGS ------------------ */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
    float TurnRate = 45.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
    float LookUpRate = 45.f;
};

