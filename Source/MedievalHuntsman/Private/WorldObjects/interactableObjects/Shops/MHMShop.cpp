// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/Shops/MHMShop.h"
#include "Kismet/KismetStringLibrary.h"
#include "Core/Helpers/MHMItemHelper.h"

void AMHMShop::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    CoinRow.DataTable = FMHMItemHelper::GetDataTable();

    for (FDataTableRowHandle& Item : Items)
    {
        Item.DataTable = FMHMItemHelper::GetDataTable();
    }
}

FText AMHMShop::GetObjectName() const
{
    TArray<FString> ItemNames;
    for (const FDataTableRowHandle& Item : Items)
    {
        const FText ItemName = FMHMItemHelper::GetName(Item.RowName);
        ItemNames.Add(ItemName.ToString());
    }
    const FText ItemNamesText = FText::FromString(UKismetStringLibrary::JoinStringArray(ItemNames, ItemSeparatorText));
    return FText::Format(FTextFormat::FromString("{0}: {1}"), ActionText, ItemNamesText);
}

const TArray<FDataTableRowHandle>& AMHMShop::GetItems() const
{
    return Items;
}

FName AMHMShop::GetCoinRowName() const
{
    return CoinRow.RowName;
}
