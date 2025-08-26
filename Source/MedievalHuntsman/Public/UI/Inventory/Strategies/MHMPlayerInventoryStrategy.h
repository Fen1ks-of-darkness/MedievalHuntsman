// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/Strategies/MHMInventoryStrategy.h"
#include "MHMPlayerInventoryStrategy.generated.h"

enum class EMHMItemType : uint8;
class UMHMEquipmentComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMPlayerInventoryStrategy : public UMHMInventoryStrategy
{
    GENERATED_BODY()

public:
    virtual void ClickedItem(const FName& RowName) const override;
    void SetPlayer(AActor* InPlayer);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<EMHMItemType, TSubclassOf<UActorComponent>> ItemTypesAndEquipmentClassesMatching;

    UPROPERTY()
    AActor* Player;
};
