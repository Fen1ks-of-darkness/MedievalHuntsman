// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MHMRowName.generated.h"

UINTERFACE(MinimalAPI)
class UMHMRowName : public UInterface
{
    GENERATED_BODY()
};

class MEDIEVALHUNTSMAN_API IMHMRowName
{
    GENERATED_BODY()

public:
    virtual void SetRowName(const FName& InRowName) = 0;
    virtual FName GetRowName() const = 0;
};
