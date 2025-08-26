// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMAddingArrow.generated.h"

UINTERFACE(MinimalAPI)
class UMHMAddingArrow : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMAddingArrow
{
    GENERATED_BODY()

public:
    virtual void AddArrow(AActor* Arrow) = 0;
};
