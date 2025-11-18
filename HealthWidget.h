#pragma once
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

UCLASS()
class GODOFWAR6_API UHealthWidget : public UUserWidget
{
    GENERATED_BODY()
public:
    UFUNCTION(BlueprintImplementableEvent)
    void SetHealthPercent(float Percent);

    UFUNCTION(BlueprintImplementableEvent)
    void SetRagePercent(float Percent);
};
