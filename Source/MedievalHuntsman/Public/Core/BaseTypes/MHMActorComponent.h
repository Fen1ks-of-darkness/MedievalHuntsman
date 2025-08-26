// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MHMActorComponent.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMActorComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    FTimerManager& GetWorldTimerManager() const;
};
