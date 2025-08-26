// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/MHMInteractData.h"
#include "UI/MHMUserWidget.h"
#include "MHMInteractWidget.generated.h"

class UTextBlock;
class UInputAction;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMInteractWidget final : public UMHMUserWidget, public IMHMInteractData
{
    GENERATED_BODY()

public:
    virtual void SetObjectName(const FText& ObjectName) const override;
    virtual void SetInteractText(const FText& InteractText) const override;

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* ObjectNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* InteractTextTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* InteractKeyTextBlock;

    virtual void NativePreConstruct() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    UInputAction* InteractAction;
};
