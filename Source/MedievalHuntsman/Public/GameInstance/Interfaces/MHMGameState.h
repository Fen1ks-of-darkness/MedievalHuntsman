// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMGameState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnLevelStartedLoading)
DECLARE_MULTICAST_DELEGATE(FOnLevelLoaded)

UINTERFACE(MinimalAPI)
class UMHMGameState : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMGameState
{
    GENERATED_BODY()

public:
    virtual void NewGame() = 0;
    virtual void ReturnToMainMenu() = 0;
    virtual void QuitGame() const = 0;
    virtual void LevelLoaded() = 0;

    virtual FOnLevelStartedLoading& OnLevelStartedLoading() = 0;
    virtual FOnLevelLoaded& OnLevelLoaded() = 0;
};
