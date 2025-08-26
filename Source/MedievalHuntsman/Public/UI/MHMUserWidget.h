// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MHMUserWidget.generated.h"

class UWidgetAnimation;
class IMHMGameState;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMUserWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void Show();
    void Hide();
    void Toggle();

protected:
    UPROPERTY(Transient, meta = (BindWidgetAnimOptional))
    UWidgetAnimation* HideAnimation;

    FTimerManager& GetWorldTimerManager() const;
    IMHMGameState* GetGameState() const;
    virtual void Update();

private:
    FWidgetAnimationDynamicEvent OnAnimationFinishedEvent;

    UFUNCTION()
    void HideAnimationFinished();
};
