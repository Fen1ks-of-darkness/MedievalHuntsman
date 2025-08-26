// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/BaseTypes/MHMActorComponent.h"

FTimerManager& UMHMActorComponent::GetWorldTimerManager() const
{
    check(GetWorld());
    return GetWorld()->GetTimerManager();
}
