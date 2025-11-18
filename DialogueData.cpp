#include "DialogueData.h"
#include "UObject/ConstructorHelpers.h"

bool UDialogueData::GetLineByIndex(int32 Index, FDialogueLine& OutLine) const
{
    if (AllLines.IsValidIndex(Index))
    {
        OutLine = AllLines[Index];
        return true;
    }
    return false;
}

bool UDialogueData::FindLine(const FString& SpeakerName, const FString& TextFragment, FDialogueLine& OutLine) const
{
    for (const FDialogueLine& L : AllLines)
    {
        if ((SpeakerName.IsEmpty() || L.SpeakerName == SpeakerName) &&
            (TextFragment.IsEmpty() || L.SubtitleText.Contains(TextFragment)))
        {
            OutLine = L;
            return true;
        }
    }
    return false;
}

void UDialogueData::PopulateSampleDialogues()
{
    AllLines.Empty();

    // --- Cinematic / tutorial intro ---
    FDialogueLine L;
    L.SpeakerName = TEXT("Narrator");
    L.SubtitleText = TEXT("Long ago, the frost crept into the world. You must rise.");
    L.VoiceAudio = nullptr; // assign a WAV in editor or via BP
    L.DelayAfterLine = 2.2f;
    AllLines.Add(L);

    // Player reaction
    L.SpeakerName = TEXT("Player");
    L.SubtitleText = TEXT("I will not fail.");
    L.VoiceAudio = nullptr;
    L.DelayAfterLine = 1.2f;
    AllLines.Add(L);

    // NPC guide
    L.SpeakerName = TEXT("Guide");
    L.SubtitleText = TEXT("Stay close. The wolves hunt in packs.");
    L.VoiceAudio = nullptr;
    L.DelayAfterLine = 1.6f;
    AllLines.Add(L);

    // Enemy grunt taunt
    L.SpeakerName = TEXT("Grunt");
    L.SubtitleText = TEXT("You are meat!");
    L.VoiceAudio = nullptr;
    L.DelayAfterLine = 1.f;
    AllLines.Add(L);

    // Boss cinematic line
    L.SpeakerName = TEXT("Boss");
    L.SubtitleText = TEXT("Foolish mortal — face oblivion.");
    L.VoiceAudio = nullptr;
    L.DelayAfterLine = 2.0f;
    AllLines.Add(L);

    // Short combat line
    L.SpeakerName = TEXT("Player");
    L.SubtitleText = TEXT("Enough!");
    L.VoiceAudio = nullptr;
    L.DelayAfterLine = 0.9f;
    AllLines.Add(L);

    // Confirm population completed
}
