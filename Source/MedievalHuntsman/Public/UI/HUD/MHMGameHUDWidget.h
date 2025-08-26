// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/MHMHUDWidget.h"
#include "MHMGameHUDWidget.generated.h"

class UMHMInventoryWidget;
class UMHMInventoryMessagesWidget;
class UMHMPlayerInventoryStrategy;
class UMHMPauseWidget;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMGameHUDWidget final : public UMHMHUDWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UMHMInventoryWidget* PlayerInventoryWidget;

    UPROPERTY(meta = (BindWidget))
    UMHMInventoryMessagesWidget* InventoryMessagesWidget;

    UPROPERTY(meta = (BindWidget))
    UMHMPauseWidget* PauseWidget;

    virtual void NativeConstruct() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<UMHMPlayerInventoryStrategy> PlayerInventoryStrategyClass;
};
