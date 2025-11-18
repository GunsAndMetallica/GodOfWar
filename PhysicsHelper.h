#pragma once
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PhysicsHelper.generated.h"

UCLASS()
class GODOFWAR6_API UPhysicsHelper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintCallable, Category="Physics")
    static void EnableRagdoll(ACharacter* Char);

    UFUNCTION(BlueprintCallable, Category="Physics")
    static void DisableRagdoll(ACharacter* Char, FVector TeleportTo);
};
