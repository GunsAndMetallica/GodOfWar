#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class GODOFWAR6_API APlayerCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    APlayerCharacter();

protected:
    virtual void BeginPlay() override;

public: 
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    // Movement
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void Turn(float Value);
    void JumpAction();
    void Dodge();

    // Combat
    void AttackAxe();
    void ThrowAxe();
    void RecallAxe();
    void AttackBlades();
    void Block();
    void RageMode();

    // Health
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
    float Health;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Player Stats")
    float MaxHealth;

    // Weapon references
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AWeaponBase* Axe;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AWeaponBase* Blades;
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class AWeaponBase* Shield;
};
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

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void Tick(float DeltaTime) override;
    virtual void BeginPlay() override;

    // Movement
    void MoveForward(float Value);
    void MoveRight(float Value);
    void LookUp(float Value);
    void Turn(float Value);
    void StartJump();
    void StopJump();
    void Dodge();

    // Combat proxies
    void PrimaryAttack();      // Axe / Blades primary
    void SecondaryAttack();    // Light / Heavy
    void ThrowWeapon();
    void RecallWeapon();
    void BlockPressed();
    void BlockReleased();
    void ActivateRage();

    // Camera
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UCameraComponent* Camera;

    // Components
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UCombatComponent* CombatComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URageMode* RageComp;

    // Controller sensitivity
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
    float TurnRate;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera")
    float LookUpRate;
};
