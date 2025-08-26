// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Animations/MHMPawnAnimInstance.h"
#include "KismetAnimationLibrary.h"
#include "Core/Helpers/MHMHelperFunctions.h"

void UMHMPawnAnimInstance::NativeInitializeAnimation()
{
    Super::NativeInitializeAnimation();
    Pawn = TryGetPawnOwner();
    Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(Pawn);
}

void UMHMPawnAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
    Super::NativeUpdateAnimation(DeltaSeconds);
    if (Pawn)
    {
        Speed = Pawn->GetVelocity().Size();
        Direction = UKismetAnimationLibrary::CalculateDirection(Pawn->GetVelocity(), Pawn->GetActorRotation());
        if (Movement)
        {
            bIsFalling = Movement->IsInAir();
        }
    }
}