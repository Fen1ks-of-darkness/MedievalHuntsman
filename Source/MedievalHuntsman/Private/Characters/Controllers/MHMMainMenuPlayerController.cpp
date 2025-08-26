// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Controllers/MHMMainMenuPlayerController.h"

void AMHMMainMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    bShowMouseCursor = true;
    SetInputMode(FInputModeUIOnly());
}
