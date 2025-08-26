// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Inventory/Strategies/MHMPlayerInventoryStrategy.h"
#include "Characters/Interfaces/MHMEquipment.h"
#include "Core/Helpers/MHMItemHelper.h"

void UMHMPlayerInventoryStrategy::ClickedItem(const FName& RowName) const
{
    Super::ClickedItem(RowName);
    check(Player);

    const EMHMItemType ItemType = FMHMItemHelper::GetType(RowName);

    if (ItemTypesAndEquipmentClassesMatching.Contains(ItemType))
    {
        const TSubclassOf<UActorComponent> EquipmentClass = ItemTypesAndEquipmentClassesMatching[ItemType];
        IMHMEquipment* Equipment = Cast<IMHMEquipment>(Player->GetComponentByClass(EquipmentClass));
        Equipment->ToggleEquip(RowName);
    }
}

void UMHMPlayerInventoryStrategy::SetPlayer(AActor* InPlayer)
{
    Player = InPlayer;
}
