// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/MHMGameState.h"
#include "MHMGameInstance.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMGameInstance final : public UGameInstance, public IMHMGameState
{
    GENERATED_BODY()
public:
    virtual void NewGame() override;
    virtual void ReturnToMainMenu() override;
    virtual void QuitGame() const override;
    virtual void LevelLoaded() override;

    virtual FOnLevelStartedLoading& OnLevelStartedLoading() override;
    virtual FOnLevelLoaded& OnLevelLoaded() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings|Levels")
    TSoftObjectPtr<UWorld> GameLevel;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Levels")
    TSoftObjectPtr<UWorld> MainMenuLevel;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Audio")
    USoundBase* GameMusic;

    UPROPERTY()
    UAudioComponent* AudioComponent;

    TSoftObjectPtr<UWorld> LoadingLevel;
    const float DelayBeforeLoading = 1.5f;

    FOnLevelStartedLoading OnLevelStartedLoadingEvent;
    FOnLevelLoaded OnLevelLoadedEvent;

    void StartOpeningLevel(const TSoftObjectPtr<UWorld>& Level);
    void OpenLevel() const;
};
