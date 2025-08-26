// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/Weapons/MHMWeapon.h"
#include "Core/Helpers/MHMItemHelper.h"

AMHMWeapon::AMHMWeapon() : Super()
{
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    SetRootComponent(SkeletalMeshComponent);
    SetActorEnableCollision(false);
}

void AMHMWeapon::SetRowName(const FName& InRowName)
{
    check(SkeletalMeshComponent);
    RowName = InRowName;
    SkeletalMeshComponent->SetSkeletalMesh(FMHMItemHelper::GetSkeletalMesh(RowName));
    SkeletalMeshComponent->SetAnimInstanceClass(FMHMItemHelper::GetAnimInstanceClass(RowName));
}

FName AMHMWeapon::GetRowName() const
{
    return RowName;
}
