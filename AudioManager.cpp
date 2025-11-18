#include "AudioManager.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

AAudioManager::AAudioManager()
{
    PrimaryActorTick.bCanEverTick = false;
    MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
    MusicComponent->bAutoActivate = false;
    RootComponent = MusicComponent;
}

void AAudioManager::BeginPlay()
{
    Super::BeginPlay();
    if (MusicCue) PlayMusic(MusicCue);
}

void AAudioManager::PlayMusic(USoundBase* Cue)
{
    if (!Cue || !MusicComponent) return;
    MusicComponent->SetSound(Cue);
    MusicComponent->Play();
}

void AAudioManager::FadeToCombatMusic()
{
    if (!CombatMusicCue || !MusicComponent) return;
    MusicComponent->FadeOut(1.0f, 0.f);
    MusicComponent->SetSound(CombatMusicCue);
    MusicComponent->FadeIn(1.0f, 1.f);
}
