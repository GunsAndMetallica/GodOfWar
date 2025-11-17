#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RageMode.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GODOFWAR6_API URageMode : public UActorComponent
{
    GENERATED_BODY()

public: 
    URageMode();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bIsRaging;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float RageDuration;

    void ActivateRage();
    void DeactivateRage();
};
