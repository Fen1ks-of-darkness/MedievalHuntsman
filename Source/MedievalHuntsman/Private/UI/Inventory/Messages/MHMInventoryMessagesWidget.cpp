// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Inventory/Messages/MHMInventoryMessagesWidget.h"
#include "Components/PanelWidget.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"
#include "UI/Inventory/Messages/MHMInventoryMessageWidget.h"

void UMHMInventoryMessagesWidget::SetInventory(IMHMInventory* InInventory) {
    check(InInventory);
    Inventory = InInventory;
    Inventory->OnAddedItem().AddUObject(this, &ThisClass::AddedItem);
    Inventory->OnRemoveItem().AddUObject(this, &ThisClass::RemoveItem);
}

void UMHMInventoryMessagesWidget::AddedItem(const FName& RowName, const uint32 Count) {
    AddInventoryMessageWidget(RowName, Count);
}

void UMHMInventoryMessagesWidget::RemoveItem(const FName& RowName, const uint32 Count) {
    AddInventoryMessageWidget(RowName, -1 * Count);
}

void UMHMInventoryMessagesWidget::AddInventoryMessageWidget(const FName& RowName, const int32 Count) {
    check(PanelWidget);
    check(Inventory);
    check(InventoryMessageWidgetClass);

    UMHMInventoryMessageWidget* InventoryMessageWidget =
        CreateWidget<UMHMInventoryMessageWidget>(this, InventoryMessageWidgetClass);
    check(InventoryMessageWidget);

    InventoryMessageWidget->SetItemName(FMHMItemHelper::GetName(RowName));
    InventoryMessageWidget->SetItemsCount(Count);
    InventoryMessageWidget->SetItemsTotal(Inventory->GetCountByRowName(RowName));

    PanelWidget->AddChild(InventoryMessageWidget);
}
