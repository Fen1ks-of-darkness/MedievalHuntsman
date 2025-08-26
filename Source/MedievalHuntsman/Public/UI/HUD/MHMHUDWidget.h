// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MHMUserWidget.h"
#include "MHMHUDWidget.generated.h"

class UMHMLoadingScreenWidget;

UCLASS(abstract)
class MEDIEVALHUNTSMAN_API UMHMHUDWidget : public UMHMUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UMHMLoadingScreenWidget* LoadingScreenWidget;

    virtual void NativeConstruct() override;
};
