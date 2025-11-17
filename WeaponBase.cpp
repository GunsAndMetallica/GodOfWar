#include "WeaponBase.h"

AWeaponBase::AWeaponBase() {
    PrimaryActorTick.bCanEverTick = false;
    Damage = 25.f;
    AttackSpeed = 1.f;
}

void AWeaponBase::Attack() {
    // Detect enemies in range & apply damage
}
