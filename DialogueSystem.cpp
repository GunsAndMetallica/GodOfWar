#include "DialogueSystem.h"
#include "Kismet/GameplayStatics.h"

ADialogueSystem::ADialogueSystem()
{
    PrimaryActorTick.bCanEverTick = false;
    CurrentIndex = 0;
}

void ADialogueSystem::BeginPlay()
{
    Super::BeginPlay();
}

void ADialogueSystem::PlayDialogue()
{
    CurrentIndex = 0;
    PlayNextLine();
}

void ADialogueSystem::PlayNextLine()
{
    if (CurrentIndex >= DialogueLines.Num())
    {
        OnDialogueFinished();
        return;
    }

    FDialogueLine Line = DialogueLines[CurrentIndex];

    // SHOW SUBTITLE (Blueprint event)
    OnSubtitleShown(Line.SpeakerName, Line.SubtitleText);

    // PLAY VOICE AUDIO
    if (Line.VoiceAudio)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), Line.VoiceAudio);
    }

    // WAIT then continue
    FTimerHandle Timer;
    GetWorldTimerManager().SetTimer(
        Timer,
        this,
        &ADialogueSystem::PlayNextLine,
        Line.DelayAfterLine + 0.2f,
        false
    );

    CurrentIndex++;
}
