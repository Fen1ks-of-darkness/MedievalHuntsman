// Copyright Epic Games, Inc. All Rights Reserved.

#include "HUD/MHMHUD.h"
#include "Blueprint/UserWidget.h"

void AMHMHUD::BeginPlay()
{
    Super::BeginPlay();

    UUserWidget* UserWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), HUDWidgetClass);
    check(UserWidget);
    UserWidget->AddToViewport();
}