#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AudioManager.generated.h"

UCLASS()
class GODOFWAR6_API AAudioManager : public AActor
{
    GENERATED_BODY()
public:
    AAudioManager();
    virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category="Audio")
    class USoundBase* MusicCue;

    UPROPERTY(EditAnywhere, Category="Audio")
    class USoundBase* CombatMusicCue;

    UPROPERTY(EditAnywhere)
    class UAudioComponent* MusicComponent;

    UFUNCTION(BlueprintCallable)
    void PlayMusic(USoundBase* Cue);

    UFUNCTION(BlueprintCallable)
    void FadeToCombatMusic();
};
