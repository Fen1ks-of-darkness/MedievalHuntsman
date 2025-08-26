// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/AI/MHMAiComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Core/Helpers/MHMHelperFunctions.h"

void UMHMAiComponent::Start(AAIController* InAIController)
{
    AIController = InAIController;
}

void UMHMAiComponent::Stop() {
    check(AIController);
    AIController->StopMovement();
}

void UMHMAiComponent::OnMoveCompleted(const bool bIsSuccess) {}

void UMHMAiComponent::SetMovementType(const EMHMMovementType& MovementType) const
{
    IMHMMovement* Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(GetControlledPawn());
    check(Movement);
    Movement->SetMovementType(MovementType);
}

void UMHMAiComponent::MoveToLocation(const FVector& Location) const
{
    check(AIController);
    AIController->MoveToLocation(Location);
}

AActor* UMHMAiComponent::GetControlledPawn() const
{
    check(AIController);
    return AIController->GetPawn();
}

FVector UMHMAiComponent::GetRandomPointInNavigableRadius(const FVector& Origin, const float Radius) const
{
    const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    check(NavSys);
    FNavLocation ResultLocation;
    NavSys->GetRandomPointInNavigableRadius(Origin, Radius, ResultLocation);

    DrawDebugSphere(GetWorld(), ResultLocation.Location, 100, 10, FColor::Green, false, 10.0f);

    return ResultLocation.Location;
}
