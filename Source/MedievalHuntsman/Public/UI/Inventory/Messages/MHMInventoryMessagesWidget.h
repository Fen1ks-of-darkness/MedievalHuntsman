// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/Messages/MHMInventoryMessageWidget.h"
#include "UI/MHMUserWidget.h"
#include "MHMInventoryMessagesWidget.generated.h"

class IMHMInventory;
class UMHMInventoryMessageWidget;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMInventoryMessagesWidget final : public UMHMUserWidget
{
    GENERATED_BODY()

public:
    void SetInventory(IMHMInventory* InInventory);

protected:
    UPROPERTY(meta = (BindWidget))
    UPanelWidget* PanelWidget;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<UMHMInventoryMessageWidget> InventoryMessageWidgetClass;

    IMHMInventory* Inventory;
    void AddedItem(const FName& RowName, const uint32 Count);
    void RemoveItem(const FName& RowName, const uint32 Count);
    void AddInventoryMessageWidget(const FName& RowName, const int32 Count);
};
