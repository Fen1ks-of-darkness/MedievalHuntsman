// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/MHMCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Components/MHMCharacterMovementComponent.h"
#include "Characters/Components/MHMHealthComponent.h"
#include "Core/Components/MHMInventoryComponent.h"
#include "Core/Components/MHMStartingItemsComponent.h"
#include "Core/Helpers/MHMHelperFunctions.h"

AMHMCharacter::AMHMCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<UMHMCharacterMovementComponent>(CharacterMovementComponentName))
{
    HealthComponent = CreateDefaultSubobject<UMHMHealthComponent>(TEXT("HealthComponent"));
    check(HealthComponent);
    HealthComponent->OnDead.AddUObject(this, &ThisClass::Dead);

    InventoryComponent = CreateDefaultSubobject<UMHMInventoryComponent>(TEXT("InventoryComponent"));
    StartingItemsComponent = CreateDefaultSubobject<UMHMStartingItemsComponent>(TEXT("StartingItemsComponent"));

    OnTakePointDamage.AddDynamic(this, &ThisClass::PointDamage);
}

void AMHMCharacter::PointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation,
                                UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                                const UDamageType* DamageType, AActor* DamageCauser)
{
    check(HealthComponent);
    const float DamageMultiplier =
        BonesAndDamageMultipliersMatching.Contains(BoneName) ? BonesAndDamageMultipliersMatching[BoneName] : 1.0f;
    HealthComponent->ReduceHealth(Damage * DamageMultiplier);
}

void AMHMCharacter::Dead()
{
    check(GetCapsuleComponent());
    check(GetMesh());

    GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

bool AMHMCharacter::CanMove() const
{
    IMHMMovement* Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(this);
    check(Movement);
    return Movement->CanMove();
}

void AMHMCharacter::AddArrow(AActor* Arrow)
{
    AddedArrows.Add(Arrow);
}

TArray<AActor*>& AMHMCharacter::GetAddedArrows()
{
    return AddedArrows;
}