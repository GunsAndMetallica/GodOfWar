#pragma once
#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

UCLASS()
class GODOFWAR6_API APlayerHUD : public AHUD
{
    GENERATED_BODY()
public:
    virtual void BeginPlay() override;

    UPROPERTY(EditDefaultsOnly, Category="UI")
    TSubclassOf<class UUserWidget> HUDWidgetClass;

    UPROPERTY()
    class UUserWidget* HUDWidget;
};
