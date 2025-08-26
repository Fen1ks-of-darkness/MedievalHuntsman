// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMHUDPlayerController.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnToggleWidget);

UINTERFACE(MinimalAPI)
class UMHMHUDPlayerController : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMHUDPlayerController
{
    GENERATED_BODY()

public:
    virtual void ContinueGame() = 0;
    virtual FOnToggleWidget& OnToggleInventoryWidget() = 0;
    virtual FOnToggleWidget& OnTogglePauseWidget() = 0;
};
