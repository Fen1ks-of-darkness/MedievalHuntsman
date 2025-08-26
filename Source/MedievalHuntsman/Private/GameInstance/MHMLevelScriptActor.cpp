// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameInstance/MHMLevelScriptActor.h"
#include "GameInstance/Interfaces/MHMGameState.h"

void AMHMLevelScriptActor::BeginPlay()
{
    Super::BeginPlay();

    FTimerHandle TimerHandle;
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::TestDelay, 1.5f);
}

void AMHMLevelScriptActor::TestDelay() const
{
    IMHMGameState* GameState = Cast<IMHMGameState>(GetGameInstance());
    check(GameState);
    GameState->LevelLoaded();
}
