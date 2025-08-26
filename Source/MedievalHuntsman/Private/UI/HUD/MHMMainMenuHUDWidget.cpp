// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/HUD/MHMMainMenuHUDWidget.h"
#include "GameInstance/Interfaces/MHMGameState.h"
#include "UI/Base/MHMButton.h"

void UMHMMainMenuHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    check(NewGameButton);
    check(QuitGameButton);

    NewGameButton->OnClicked().AddDynamic(this, &ThisClass::NewGameClicked);
    QuitGameButton->OnClicked().AddDynamic(this, &ThisClass::QuitGameClicked);
}

void UMHMMainMenuHUDWidget::NewGameClicked()
{
    check(GetGameState());
    GetGameState()->NewGame();
}

void UMHMMainMenuHUDWidget::QuitGameClicked()
{
    check(GetGameState());
    GetGameState()->QuitGame();
}
