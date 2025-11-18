#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sound/SoundBase.h"
#include "DialogueSystem.generated.h"

USTRUCT(BlueprintType)
struct FDialogueLine
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SpeakerName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SubtitleText;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USoundBase* VoiceAudio;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DelayAfterLine = 1.0f;
};

UCLASS()
class GODOFWAR6_API ADialogueSystem : public AActor
{
    GENERATED_BODY()

public:
    ADialogueSystem();

protected:
    virtual void BeginPlay() override;

public:
    UFUNCTION(BlueprintCallable)
    void PlayDialogue();

    UFUNCTION(BlueprintCallable)
    void PlayNextLine();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
    TArray<FDialogueLine> DialogueLines;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int32 CurrentIndex;

    UFUNCTION(BlueprintImplementableEvent)
    void OnSubtitleShown(const FString& Speaker, const FString& Text);

    UFUNCTION(BlueprintImplementableEvent)
    void OnDialogueFinished();
};
