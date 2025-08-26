// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Helpers/MHMItemHelper.h"
#include "Core/BaseTypes/MHMCoreTypes.h"
#include "Core/Helpers/MHMDataTableHelper.h"
#include "Core/Settings/MHMGameSettings.h"

const UDataTable* FMHMItemHelper::GetDataTable()
{
    const UMHMGameSettings* GameSettings = GetDefault<UMHMGameSettings>();
    check(GameSettings);
    return GameSettings->ItemsDataTable.LoadSynchronous();
}

FMHMItemInfo* FMHMItemHelper::GetInfo(const FName& RowName)
{
    return FMHMDataTableHelper::FindRow<FMHMItemInfo>(GetDataTable(), RowName);
}

FText FMHMItemHelper::GetName(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->Name;
}

EMHMItemType FMHMItemHelper::GetType(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->ItemType;
}

UStaticMesh* FMHMItemHelper::GetStaticMesh(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->StaticMesh;
}

USkeletalMesh* FMHMItemHelper::GetSkeletalMesh(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->SkeletalMesh;
}

TSubclassOf<UAnimInstance> FMHMItemHelper::GetAnimInstanceClass(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->AnimInstanceClass;
}

float FMHMItemHelper::GetDamage(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->Damage;
}

float FMHMItemHelper::GetPrice(const FName& RowName)
{
    const FMHMItemInfo* ItemInfo = GetInfo(RowName);
    check(ItemInfo);
    return ItemInfo->Price;
}
