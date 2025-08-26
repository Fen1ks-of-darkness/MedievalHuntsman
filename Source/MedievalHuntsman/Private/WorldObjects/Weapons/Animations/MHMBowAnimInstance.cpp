// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/Weapons/Animations/MHMBowAnimInstance.h"
#include "Core/Interfaces/MHMBowFighting.h"

void UMHMBowAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    BowFighting = Cast<IMHMBowFighting>(GetOwningActor());
}

void UMHMBowAnimInstance::NativeUpdateAnimation(const float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (BowFighting)
    {
        Charge = BowFighting->GetCharge();
    }
}
