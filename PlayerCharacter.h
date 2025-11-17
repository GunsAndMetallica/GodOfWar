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
