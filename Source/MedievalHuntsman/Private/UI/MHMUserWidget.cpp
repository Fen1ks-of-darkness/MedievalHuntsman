// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/MHMUserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameInstance/Interfaces/MHMGameState.h"

void UMHMUserWidget::Show()
{
    if (IsVisible()) return;
    SetVisibility(ESlateVisibility::Visible);
}

void UMHMUserWidget::Hide()
{
    if (!IsVisible()) return;
    if (HideAnimation)
    {
        StopAllAnimations();
        OnAnimationFinishedEvent.BindDynamic(this, &ThisClass::HideAnimationFinished);
        BindToAnimationFinished(HideAnimation, OnAnimationFinishedEvent);
        PlayAnimation(HideAnimation);
    }
    else
    {
        HideAnimationFinished();
    }
}

void UMHMUserWidget::HideAnimationFinished()
{
    SetVisibility(ESlateVisibility::Hidden);
}

void UMHMUserWidget::Toggle()
{
    IsVisible() ? Hide() : Show();
}

FTimerManager& UMHMUserWidget::GetWorldTimerManager() const
{
    check(GetWorld());
    return GetWorld()->GetTimerManager();
}

IMHMGameState* UMHMUserWidget::GetGameState() const
{
    return Cast<IMHMGameState>(UGameplayStatics::GetGameInstance(this));
}

void UMHMUserWidget::Update() {}
