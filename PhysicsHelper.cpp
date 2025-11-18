#include "PhysicsHelper.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void UPhysicsHelper::EnableRagdoll(ACharacter* Char)
{
    if (!Char) return;
    USkeletalMeshComponent* Mesh = Char->GetMesh();
    if (!Mesh) return;
    Mesh->SetCollisionProfileName("Ragdoll");
    Mesh->SetSimulatePhysics(true);
    Char->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    Char->DisableInput(nullptr);
}

void UPhysicsHelper::DisableRagdoll(ACharacter* Char, FVector TeleportTo)
{
    if (!Char) return;
    USkeletalMeshComponent* Mesh = Char->GetMesh();
    if (!Mesh) return;

    Mesh->SetSimulatePhysics(false);
    Char->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    Char->SetActorLocation(TeleportTo);
    Char->EnableInput(nullptr);
    Mesh->SetCollisionProfileName("CharacterMesh");
}
