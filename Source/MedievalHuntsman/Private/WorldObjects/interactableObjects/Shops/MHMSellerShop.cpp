// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/Shops/MHMSellerShop.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"

void AMHMSellerShop::DoInteract(AActor* OtherActor)
{
    Super::DoInteract(OtherActor);
    IMHMInventory* Inventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(OtherActor);
    if (Inventory)
    {
        if (Inventory->RemoveItem(GetCoinRowName(), GetNeedCoins()))
        {
            const TArray<FDataTableRowHandle>& SellingItem = GetItems();
            for (const FDataTableRowHandle& Item : SellingItem)
            {
                Inventory->AddItem(Item.RowName);
            }
        }
    }
}

float AMHMSellerShop::GetNeedCoins() const
{
    const TArray<FDataTableRowHandle>& BuyingItems = GetItems();
    float NeedCoins = 0.0f;
    for (const FDataTableRowHandle& Item : BuyingItems)
    {
        NeedCoins += FMHMItemHelper::GetPrice(Item.RowName);
    }
    return NeedCoins;
}
