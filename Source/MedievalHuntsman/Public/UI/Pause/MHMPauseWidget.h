// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/MHMUserWidget.h"
#include "MHMPauseWidget.generated.h"

class UMHMButton;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMPauseWidget final : public UMHMUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UMHMButton* ContinueButton;

    UPROPERTY(meta = (BindWidget))
    UMHMButton* BackToMainMenuButton;

    UPROPERTY(meta = (BindWidget))
    UMHMButton* QuitGameButton;

    virtual void NativeConstruct() override;

private:
    UFUNCTION()
    void ContinueGameClicked();

    UFUNCTION()
    void ReturnToMainMenuClicked();

    UFUNCTION()
    void QuitGameClicked();
};
