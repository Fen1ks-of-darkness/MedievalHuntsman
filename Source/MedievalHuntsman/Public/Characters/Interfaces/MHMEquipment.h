// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMEquipment.generated.h"

UINTERFACE(MinimalAPI)
class UMHMEquipment : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMEquipment
{
    GENERATED_BODY()

public:
    virtual void ToggleEquip(const FName& RowName) = 0;
    virtual FName GetEquippedItemRowName() const = 0;
};
