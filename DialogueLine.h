#pragma once
#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "DialogueLine.generated.h"

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
    float Duration = 2.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float DelayAfterLine = 0.5f;
};
