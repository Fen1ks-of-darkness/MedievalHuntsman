// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMBowFighting.generated.h"

UINTERFACE(MinimalAPI)
class UMHMBowFighting : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMBowFighting
{
    GENERATED_BODY()

public:
    virtual void StartCharge() = 0;
    virtual void StopCharge() = 0;
    virtual void Fire() = 0;
    virtual float GetCharge() const = 0;
};
