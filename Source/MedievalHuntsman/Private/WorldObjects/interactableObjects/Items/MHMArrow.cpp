// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/Items/MHMArrow.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Interfaces/MHMAddingArrow.h"

AMHMArrow::AMHMArrow() : Super()
{
    SetActorEnableCollision(false);

    ProjectileMovementComponent =
        CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
    check(ProjectileMovementComponent);
    ProjectileMovementComponent->SetAutoActivate(false);
    ProjectileMovementComponent->bRotationFollowsVelocity = true;
}

void AMHMArrow::Fire(const float Charge)
{
    check(StaticMeshComponent);
    check(ProjectileMovementComponent);

    SetActorEnableCollision(true);
    StaticMeshComponent->SetNotifyRigidBodyCollision(true);

    StaticMeshComponent->OnComponentHit.AddDynamic(this, &ThisClass::OnHit);
    ProjectileMovementComponent->Velocity = GetActorForwardVector() * FMath::Lerp(MinSpeed, MaxSpeed, Charge);
    ProjectileMovementComponent->Activate();
}

void AMHMArrow::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
                      FVector NormalImpulse, const FHitResult& Hit)
{
    check(OtherActor);
    check(StaticMeshComponent);
    check(ProjectileMovementComponent);

    ProjectileMovementComponent->Deactivate();
    StaticMeshComponent->SetNotifyRigidBodyCollision(false);

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = Hit;

    OtherActor->TakeDamage(DamageAmount, PointDamageEvent, nullptr, GetOwner());
    AttachToComponent(OtherComp, FAttachmentTransformRules(EAttachmentRule::KeepWorld, true), Hit.BoneName);
    UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation());

    if (IMHMAddingArrow* AddingArrow = Cast<IMHMAddingArrow>(OtherActor))
    {
        AddingArrow->AddArrow(this);
    }
}

void AMHMArrow::SetDamageAmount(const float InDamageAmount)
{
    check(InDamageAmount >= 0);
    DamageAmount = InDamageAmount;
}

bool AMHMArrow::CanInteract() const
{
    check(ProjectileMovementComponent);
    return !ProjectileMovementComponent->IsActive();
}
