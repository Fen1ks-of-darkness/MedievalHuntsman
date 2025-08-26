// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MHMUserWidget.h"
#include "MHMInventorySlotWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInventorySlotClicked, const FName&);

class UButton;
class UImage;
class UTextBlock;

struct FMHMItemSlot
{
    FName RowName;
    uint32 Count;
    bool bIsActive;
};

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMInventorySlotWidget final : public UMHMUserWidget
{
    GENERATED_BODY()
     
public:
    FOnInventorySlotClicked OnInventorySlotClicked;
    virtual void NativeConstruct() override;
    void SetItem(const FMHMItemSlot& InItemSlot);

protected:
    UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
    UButton* InventorySlotButton;

    UPROPERTY(meta = (BindWidget))
    UImage* Thumbnail;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* ItemName;

    UFUNCTION(BlueprintPure)
    bool IsActive() const;

private:
    FMHMItemSlot ItemSlot;

    UFUNCTION()
    void InventorySlotClicked();

    FText GetItemNameText(const FText& Name) const;
};
