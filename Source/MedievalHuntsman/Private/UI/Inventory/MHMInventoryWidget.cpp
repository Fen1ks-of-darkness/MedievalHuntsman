// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Inventory/MHMInventoryWidget.h"
#include "Components/PanelWidget.h"
#include "Characters/Interfaces/MHMEquipment.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Interfaces/MHMInventory.h"
#include "UI/Inventory/MHMInventorySlotWidget.h"
#include "UI/Inventory/Strategies/MHMInventoryStrategy.h"

void UMHMInventoryWidget::SetInventory(IMHMInventory* InInventory)
{
    check(InInventory);
    Inventory = InInventory;
    Inventory->OnInventoryChanged().AddUObject(this, &ThisClass::Update);
    Update();
}

void UMHMInventoryWidget::SetStrategy(UMHMInventoryStrategy* InStrategy)
{
    Strategy = InStrategy;
}

void UMHMInventoryWidget::Update()
{
    Super::Update();

    check(Inventory);
    check(PanelWidget);
    check(InventorySlotWidgetClass);

    Equipments = FMHMHelperFunctions::GetComponentsByInterface<IMHMEquipment>(GetOwningPlayerPawn());

    PanelWidget->ClearChildren();
    const TMap<FName, uint32>& Items = Inventory->GetItems();
    for (const TPair<FName, uint32>& Item : Items)
    {
        UMHMInventorySlotWidget* InventorySlotWidget =
            CreateWidget<UMHMInventorySlotWidget>(this, InventorySlotWidgetClass);
        check(InventorySlotWidget);

        const FMHMItemSlot ItemSlot{Item.Key, Item.Value, IsEquppied(Item.Key)};
        InventorySlotWidget->SetItem(ItemSlot);
        InventorySlotWidget->OnInventorySlotClicked.AddUObject(this, &ThisClass::InventorySlotClicked);

        PanelWidget->AddChild(InventorySlotWidget);
    }
}

bool UMHMInventoryWidget::IsEquppied(const FName& RowName)
{
    for (const IMHMEquipment* Equipment : Equipments)
    {
        check(Equipment);
        if (Equipment->GetEquippedItemRowName().IsEqual(RowName)) return true;
    }
    return false;
}

void UMHMInventoryWidget::InventorySlotClicked(const FName& RowName)
{
    check(Strategy);
    Strategy->ClickedItem(RowName);
    Update();
}
