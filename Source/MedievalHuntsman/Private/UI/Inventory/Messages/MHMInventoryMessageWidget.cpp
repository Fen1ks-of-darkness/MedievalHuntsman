// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Inventory/Messages/MHMInventoryMessageWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UMHMInventoryMessageWidget::NativeConstruct()
{
    Super::NativeConstruct();
    FTimerHandle TimerHandle; 
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::RemoveFromParent, DelayBeforeRemove);
}

void UMHMInventoryMessageWidget::SetItemName(const FText& ItemName) const
{
    check(ItemNameTextBlock);
    ItemNameTextBlock->SetText(ItemName);
}

void UMHMInventoryMessageWidget::SetItemsCount(const int32 ItemsCount) const
{
    check(ItemsCountTextBlock);
    ItemsCountTextBlock->SetText(FText::AsNumber(FMath::Abs(ItemsCount)));
    SetType(ItemsCount > 0);
}

void UMHMInventoryMessageWidget::SetType(const bool bIsAdded) const
{
    check(PlusImage);
    check(MinusImage);
    if (bIsAdded)
    {
        MinusImage->SetVisibility(ESlateVisibility::Collapsed);
        PlusImage->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        MinusImage->SetVisibility(ESlateVisibility::Visible);
        PlusImage->SetVisibility(ESlateVisibility::Collapsed);
    }
}

void UMHMInventoryMessageWidget::SetItemsTotal(const uint32 ItemTotal) const
{
    check(ItemNameTextBlock);
    ItemTotalTextBlock->SetText(FText::AsNumber(ItemTotal));
}
