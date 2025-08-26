// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/AI/MHMPatrolAiComponent.h"
#include "Characters/Interfaces/MHMMovement.h"

void UMHMPatrolAiComponent::Start(AAIController* InAIController)
{
    Super::Start(InAIController);
    SetMovementType(EMHMMovementType::Walking);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::GoToNextLocation, DelayAfterSuccess);
}

void UMHMPatrolAiComponent::Stop()
{
    Super::Stop();
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void UMHMPatrolAiComponent::OnMoveCompleted(const bool bIsSuccess)
{
    Super::OnMoveCompleted(bIsSuccess);
    const float RealDelay = bIsSuccess ? DelayAfterSuccess : DelayAfterFail;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::GoToNextLocation, RealDelay);
}

void UMHMPatrolAiComponent::SetStartLocation(const FVector& InStartLocation)
{
    StartLocation = InStartLocation;
}

void UMHMPatrolAiComponent::GoToNextLocation() const
{
    MoveToLocation(GetRandomPointInNavigableRadius(StartLocation, Radius));
}
