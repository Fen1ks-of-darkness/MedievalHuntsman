// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Controllers/MHMPlayerController.h"
#include "MHMMainMenuPlayerController.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API AMHMMainMenuPlayerController final : public AMHMPlayerController
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;
};
