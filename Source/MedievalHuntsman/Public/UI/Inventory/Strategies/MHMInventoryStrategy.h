// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MHMInventoryStrategy.generated.h"

UCLASS(Abstract, Blueprintable)
class MEDIEVALHUNTSMAN_API UMHMInventoryStrategy : public UObject
{
    GENERATED_BODY()

public:
    virtual void ClickedItem(const FName& RowName) const;
};
