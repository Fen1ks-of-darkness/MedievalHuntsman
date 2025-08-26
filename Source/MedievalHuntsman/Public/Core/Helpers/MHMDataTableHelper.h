// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"

class MEDIEVALHUNTSMAN_API FMHMDataTableHelper final
{
public:
    template <class T>
    static T* FindRow(const UDataTable* DataTable, const FName RowName)
    {
        check(DataTable);
        return DataTable->FindRow<T>(RowName, ContextString, true);
    }

    template <class T>
    static T* GetFirstRow(const UDataTable* DataTable)
    {
        check(DataTable);
        TArray<T*> Rows;
        DataTable->GetAllRows<T>(ContextString, Rows);
        check(Rows.Num() > 0);
        return Rows[0];
    }

    template <class T>
    static void GetAllRows(const UDataTable* DataTable, TArray<T*>& Rows)
    {
        check(DataTable);
        DataTable->GetAllRows<T>(ContextString, Rows);
    }

    static TArray<FName> GetRowsName(const UDataTable* DataTable);
    static bool RowExists(const UDataTable* DataTable, const FName& RowName);

private:
    static const FString ContextString;
};
