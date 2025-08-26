// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

enum class EMHMItemType : uint8;
class UDataTable;
class UStaticMesh;
struct FMHMItemInfo;

class MEDIEVALHUNTSMAN_API FMHMItemHelper final
{
public:
    static const UDataTable* GetDataTable();
    static FMHMItemInfo* GetInfo(const FName& RowName);
    static FText GetName(const FName& RowName);
    static EMHMItemType GetType(const FName& RowName);
    static UStaticMesh* GetStaticMesh(const FName& RowName);
    static USkeletalMesh* GetSkeletalMesh(const FName& RowName);
    static TSubclassOf<UAnimInstance> GetAnimInstanceClass(const FName& RowName);
    static float GetDamage(const FName& RowName);
    static float GetPrice(const FName& RowName);
};
