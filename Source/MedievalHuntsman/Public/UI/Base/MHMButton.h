// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "UI/MHMUserWidget.h"
#include "MHMButton.generated.h"

class UButton;
class UTextBlock;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMButton final : public UMHMUserWidget
{
    GENERATED_BODY()

public:
    FOnButtonClickedEvent& OnClicked() const;

protected:
    UPROPERTY(EditAnywhere, Category = "Settings")
    FText TextButton;

    UPROPERTY(meta = (BindWidget))
    UButton* Button;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* TextBlock;

    virtual void NativePreConstruct() override;
};
