#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"

void APlayerHUD::BeginPlay()
{
    Super::BeginPlay();
    if (HUDWidgetClass)
    {
        HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
        if (HUDWidget) HUDWidget->AddToViewport();
    }
}
