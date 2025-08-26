// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameInstance/MHMGameInstance.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMHMGameInstance::NewGame()
{
    StartOpeningLevel(GameLevel);
}

void UMHMGameInstance::StartOpeningLevel(const TSoftObjectPtr<UWorld>& Level)
{
    check(GetWorld());

    LoadingLevel = Level;
    OnLevelStartedLoadingEvent.Broadcast();

    UGameplayStatics::SetGamePaused(this, false);
    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ThisClass::OpenLevel, DelayBeforeLoading);
}

void UMHMGameInstance::OpenLevel() const
{
    UGameplayStatics::OpenLevelBySoftObjectPtr(this, LoadingLevel);
}

void UMHMGameInstance::ReturnToMainMenu()
{
    StartOpeningLevel(MainMenuLevel);
}

void UMHMGameInstance::QuitGame() const
{
    UKismetSystemLibrary::QuitGame(this, GetPrimaryPlayerController(), EQuitPreference::Quit, true);
}

void UMHMGameInstance::LevelLoaded()
{
    OnLevelLoadedEvent.Broadcast();
    if (!AudioComponent)
    {
        AudioComponent = UGameplayStatics::SpawnSound2D(this, GameMusic, 1.0f, 1.0f, 0.0f, nullptr, true);
        check(AudioComponent);
        AudioComponent->Play();
    }
}

FOnLevelStartedLoading& UMHMGameInstance::OnLevelStartedLoading()
{
    return OnLevelStartedLoadingEvent;
}

FOnLevelLoaded& UMHMGameInstance::OnLevelLoaded()
{
    return OnLevelLoadedEvent;
}
