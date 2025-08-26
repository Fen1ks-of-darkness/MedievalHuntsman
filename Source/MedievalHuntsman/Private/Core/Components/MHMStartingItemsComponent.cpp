// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Components/MHMStartingItemsComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Interfaces/MHMInventory.h"

void UMHMStartingItemsComponent::BeginPlay()
{
    Super::BeginPlay();
    AddStartingItems();
}

void UMHMStartingItemsComponent::AddStartingItems()
{
    IMHMInventory* Inventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(GetOwner());
    check(Inventory);

    for (const FStartingItem& StartingItem : StartingItems)
    {
        for (uint32 i = 0; i < StartingItem.Count; ++i)
        {
            if (UKismetMathLibrary::RandomBoolWithWeight(StartingItem.Probability))
            {
                Inventory->AddItem(StartingItem.ItemRow.RowName);
            }
        }
    }
}
