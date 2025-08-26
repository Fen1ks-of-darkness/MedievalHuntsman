// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/interactableObjects/Shops/MHMShop.h"
#include "MHMSellerShop.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMSellerShop final : public AMHMShop
{
    GENERATED_BODY()

protected:
    virtual void DoInteract(AActor* OtherActor) override;

private:
    float GetNeedCoins() const;
};
