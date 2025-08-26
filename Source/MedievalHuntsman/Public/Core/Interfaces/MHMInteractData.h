// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMInteractData.generated.h"

UINTERFACE(MinimalAPI)
class UMHMInteractData : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMInteractData
{
    GENERATED_BODY()

public:
    virtual void SetObjectName(const FText& ObjectName) const = 0;
    virtual void SetInteractText(const FText& InteractText) const = 0;
};
