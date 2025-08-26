// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/MHMHUDWidget.h"
#include "MHMMainMenuHUDWidget.generated.h"

class UMHMButton;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMMainMenuHUDWidget final : public UMHMHUDWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UMHMButton* NewGameButton;

    UPROPERTY(meta = (BindWidget))
    UMHMButton* QuitGameButton;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void NewGameClicked();

    UFUNCTION()
    void QuitGameClicked();
};
