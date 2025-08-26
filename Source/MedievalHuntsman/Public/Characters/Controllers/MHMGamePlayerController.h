// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Characters/Controllers/MHMPlayerController.h"
#include "Characters/Interfaces/MHMHUDPlayerController.h"
#include "MHMGamePlayerController.generated.h"

class UInputMappingContext; 
class UInputAction;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMGamePlayerController final : public AMHMPlayerController, public IMHMHUDPlayerController
{
    GENERATED_BODY()

public:
    virtual void ContinueGame() override;
    virtual FOnToggleWidget& OnToggleInventoryWidget() override;
    virtual FOnToggleWidget& OnTogglePauseWidget() override;

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* InventoryAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* PauseAction;

    FOnToggleWidget OnToggleInventoryWidgetEvent;
    FOnToggleWidget OnTogglePauseWidgetEvent;

    bool bIsInventoryShown = false;
    bool bIsPauseShown = false;

    void ToggleInventoryWidget();
    void TogglePauseWidget();
    void UpdateInputMode();
};
