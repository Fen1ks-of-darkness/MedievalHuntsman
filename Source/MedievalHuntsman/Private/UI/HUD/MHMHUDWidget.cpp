// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/HUD/MHMHUDWidget.h"
#include "GameInstance/Interfaces/MHMGameState.h"
#include "UI/LoadingScreen/MHMLoadingScreenWidget.h"

void UMHMHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    check(LoadingScreenWidget);
    IMHMGameState* GameState = GetGameState();
    check(GameState);
    GameState->OnLevelStartedLoading().AddUObject(LoadingScreenWidget, &ThisClass::Show);
    GameState->OnLevelLoaded().AddUObject(LoadingScreenWidget, &ThisClass::Hide);
}
