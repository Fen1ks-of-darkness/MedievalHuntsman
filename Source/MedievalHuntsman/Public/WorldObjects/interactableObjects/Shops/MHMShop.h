// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "WorldObjects/interactableObjects/MHMInteractableObject.h"
#include "MHMShop.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMShop : public AMHMInteractableObject
{
    GENERATED_BODY()

public:
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    virtual FText GetObjectName() const override;
    const TArray<FDataTableRowHandle>& GetItems() const;
    FName GetCoinRowName() const;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings|Main")
    FDataTableRowHandle CoinRow;

    UPROPERTY(EditAnywhere, Category = "Settings|Main")
    TArray<FDataTableRowHandle> Items;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Text")
    FText ActionText;

    FString ItemSeparatorText{TEXT(", ")};
};
