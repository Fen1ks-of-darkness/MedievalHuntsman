// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MHMUserWidget.h"
#include "MHMInventoryMessageWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMInventoryMessageWidget final : public UMHMUserWidget
{
    GENERATED_BODY()

public:
    void SetItemName(const FText& ItemName) const;
    void SetItemsCount(const int32 ItemsCount) const;
    void SetItemsTotal(const uint32 ItemTotal) const;

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemsCountTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemTotalTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage* PlusImage;

    UPROPERTY(meta = (BindWidget))
    UImage* MinusImage;

    virtual void NativeConstruct() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Seconds"))
    float DelayBeforeRemove = 5.0f;

    void SetType(const bool bIsAdded) const;
};
