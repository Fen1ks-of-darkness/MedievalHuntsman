// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/AI/MHMEscapeAiComponent.h"
#include "Characters/Interfaces/MHMMovement.h"

void UMHMEscapeAiComponent::Start(AAIController* InAIController)
{
    Super::Start(InAIController);
    SetMovementType(EMHMMovementType::Sprinting);
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::GoToNextLocation, TimerRate, true, 0.0f);
}

void UMHMEscapeAiComponent::GoToNextLocation()
{
    check(GetControlledPawn());
    if (GetControlledPawn()->GetDistanceTo(Enemy) < GetCurrentSafeDistance())
    {
        MoveToLocation(GetNextLocation());
    }
    else
    {
        bDamageHasBeenReceived = false;
        OnEscaped.Broadcast();
    }
}

float UMHMEscapeAiComponent::GetCurrentSafeDistance() const
{
    return bDamageHasBeenReceived ? SafeDistanceAfterHit : SafeDistance;
}

FVector UMHMEscapeAiComponent::GetNextLocation() const
{
    check(Enemy);
    check(GetControlledPawn());
    FVector Delta = GetControlledPawn()->GetActorLocation() - Enemy->GetActorLocation();
    Delta.Normalize();
    const FVector Origin = GetControlledPawn()->GetActorLocation() + Delta * DistanceForEscape;

    return GetRandomPointInNavigableRadius(Origin, Radius);
}

void UMHMEscapeAiComponent::Stop() {
    Super::Stop();
    GetWorldTimerManager().ClearTimer(TimerHandle);
}

void UMHMEscapeAiComponent::SetEnemy(const AActor* InEnemy)
{
    Enemy = InEnemy;
}

void UMHMEscapeAiComponent::DamageHasBeenReceived()
{
    bDamageHasBeenReceived = true;
}
