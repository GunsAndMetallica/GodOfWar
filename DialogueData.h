#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sound/SoundBase.h"
#include "DialogueSystem.h" // for FDialogueLine
#include "DialogueData.generated.h"

/**
 * Simple UObject container for dialogue lines.
 * Populate here with sample dialogues. You can later convert to DataAsset.
 */
UCLASS(BlueprintType)
class GODOFWAR6_API UDialogueData : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
    TArray<FDialogueLine> AllLines;

    // Return a copy of the line by index (safe)
    UFUNCTION(BlueprintCallable, Category="Dialogue")
    bool GetLineByIndex(int32 Index, FDialogueLine& OutLine) const;

    // Find first line matching speaker+text fragment (optional)
    UFUNCTION(BlueprintCallable, Category="Dialogue")
    bool FindLine(const FString& SpeakerName, const FString& TextFragment, FDialogueLine& OutLine) const;

    // Convenience: fill default sample dialogues (call in BeginPlay from some manager or in editor)
    UFUNCTION(CallInEditor, Category="Dialogue")
    void PopulateSampleDialogues();
};
