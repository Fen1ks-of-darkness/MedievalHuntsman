// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Helpers/MHMDataTableHelper.h"

const FString FMHMDataTableHelper::ContextString(TEXT("DataTable"));

TArray<FName> FMHMDataTableHelper::GetRowsName(const UDataTable* DataTable)
{
    check(DataTable);
    return DataTable->GetRowNames();
}

bool FMHMDataTableHelper::RowExists(const UDataTable* DataTable, const FName& RowName)
{
    check(DataTable);
    return DataTable->GetRowNames().Contains(RowName);
}