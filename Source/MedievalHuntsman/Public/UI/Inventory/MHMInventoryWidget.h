// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MHMUserWidget.h"
#include "MHMInventoryWidget.generated.h"

class IMHMEquipment;
class IMHMInventory;
class UMHMInventoryStrategy;
class UMHMInventorySlotWidget;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMInventoryWidget final : public UMHMUserWidget
{
    GENERATED_BODY()

public:
    void SetInventory(IMHMInventory* InInventory);
    void SetStrategy(UMHMInventoryStrategy* InStrategy);

protected:
    UPROPERTY(meta = (BindWidget))
    UPanelWidget* PanelWidget;

    virtual void Update() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<UMHMInventorySlotWidget> InventorySlotWidgetClass;

    UPROPERTY()
    UMHMInventoryStrategy* Strategy;

    TArray<IMHMEquipment*> Equipments;
    IMHMInventory* Inventory;

    bool IsEquppied(const FName& RowName);
    void InventorySlotClicked(const FName& RowName);
};
