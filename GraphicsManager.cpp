#include "GraphicsManager.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"

AGraphicsManager::AGraphicsManager()
{
    PrimaryActorTick.bCanEverTick = false;
    bEnableHighQualityPostProcess = true;
}

void AGraphicsManager::BeginPlay()
{
    Super::BeginPlay();
    ConfigureQualitySettings();
}

void AGraphicsManager::ConfigureQualitySettings()
{
    if (!GEngine) return;
    if (bEnableHighQualityPostProcess)
    {
        // high-level toggles: increase shadow quality, view distance, etc.
        Scalability::FQualityLevels Quality;
        Quality.SetFromSingleQualityLevel(3);
        Scalability::SetQualityLevels(Quality);
    }
    else
    {
        Scalability::FQualityLevels Quality;
        Quality.SetFromSingleQualityLevel(1);
        Scalability::SetQualityLevels(Quality);
    }
}
