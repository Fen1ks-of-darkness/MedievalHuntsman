// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Pause/MHMPauseWidget.h"
#include "Characters/Interfaces/MHMHUDPlayerController.h"
#include "GameInstance/Interfaces/MHMGameState.h"
#include "UI/Base/MHMButton.h"

void UMHMPauseWidget::NativeConstruct()
{
    Super::NativeConstruct();
    check(ContinueButton);
    check(BackToMainMenuButton);
    check(QuitGameButton);

    ContinueButton->OnClicked().AddDynamic(this, &ThisClass::ContinueGameClicked);
    BackToMainMenuButton->OnClicked().AddDynamic(this, &ThisClass::ReturnToMainMenuClicked);
    QuitGameButton->OnClicked().AddDynamic(this, &ThisClass::QuitGameClicked);
}

void UMHMPauseWidget::ContinueGameClicked()
{
    IMHMHUDPlayerController* HUDPlayerController = Cast<IMHMHUDPlayerController>(GetOwningPlayer());
    check(HUDPlayerController);
    HUDPlayerController->ContinueGame();
}

void UMHMPauseWidget::ReturnToMainMenuClicked()
{
    check(GetGameState());
    GetGameState()->ReturnToMainMenu();
}

void UMHMPauseWidget::QuitGameClicked()
{
    check(GetGameState());
    GetGameState()->QuitGame();
}
