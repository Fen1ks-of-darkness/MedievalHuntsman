// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/interactableObjects/Shops/MHMShop.h"
#include "MHMBuyerShop.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMBuyerShop final : public AMHMShop
{
    GENERATED_BODY()

protected:
    virtual void DoInteract(AActor* OtherActor) override;
};
