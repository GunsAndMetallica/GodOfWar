#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GraphicsManager.generated.h"

UCLASS()
class GODOFWAR6_API AGraphicsManager : public AActor
{
    GENERATED_BODY()
public:
    AGraphicsManager();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category="Rendering")
    bool bEnableHighQualityPostProcess;

    UFUNCTION(BlueprintCallable, Category="Rendering")
    void ConfigureQualitySettings();
};
