// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/Shops/MHMBuyerShop.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"

void AMHMBuyerShop::DoInteract(AActor* OtherActor)
{
    Super::DoInteract(OtherActor);
    IMHMInventory* Inventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(OtherActor);
    if (Inventory)
    {
        const TArray<FDataTableRowHandle>& BuyingItems = GetItems();
        for (const FDataTableRowHandle& Item : BuyingItems)
        {
            const float Price = FMHMItemHelper::GetPrice(Item.RowName);
            const uint32 Count = Inventory->GetCountByRowName(Item.RowName);
            if (Count > 0)
            {
                Inventory->RemoveItem(Item.RowName, Count);
                Inventory->AddItem(GetCoinRowName(), Count * Price);
            }
        }
    }
}
