#include "RageMode.h"
#include "TimerManager.h"

URageMode::URageMode() {
    bIsRaging = false;
    RageDuration = 10.f; // 10 seconds
}

void URageMode::ActivateRage() {
    bIsRaging = true;
    // Increase damage, speed, and play effects
    GetWorld()->GetTimerManager().SetTimer(
        [this]() { DeactivateRage(); },
        RageDuration, false
    );
}

void URageMode::DeactivateRage() {
    bIsRaging = false;
    // Reset damage & speed
}
