// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Inventory/MHMInventorySlotWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Core/BaseTypes/MHMCoreTypes.h"
#include "Core/Helpers/MHMItemHelper.h"

void UMHMInventorySlotWidget::NativeConstruct()
{
    Super::NativeConstruct();

    check(InventorySlotButton);
    InventorySlotButton->OnClicked.AddUniqueDynamic(this, &ThisClass::InventorySlotClicked);
}

bool UMHMInventorySlotWidget::IsActive() const
{
    return ItemSlot.bIsActive;
}

void UMHMInventorySlotWidget::InventorySlotClicked()
{
    OnInventorySlotClicked.Broadcast(ItemSlot.RowName);
}

void UMHMInventorySlotWidget::SetItem(const FMHMItemSlot& InItemSlot)
{
    check(Thumbnail);
    check(ItemName);

    ItemSlot = InItemSlot;
    const FMHMItemInfo* ItemInfo = FMHMItemHelper::GetInfo(ItemSlot.RowName);
    check(ItemInfo);

    Thumbnail->SetBrushFromTexture(ItemInfo->Thumbnails);
    ItemName->SetText(GetItemNameText(ItemInfo->Name));
}

FText UMHMInventorySlotWidget::GetItemNameText(const FText& Name) const
{
    return FText::Format(FTextFormat::FromString("{0} x {1}"), Name, ItemSlot.Count);
}