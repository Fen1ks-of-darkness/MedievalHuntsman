// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MHMLevelScriptActor.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMLevelScriptActor final : public ALevelScriptActor
{
    GENERATED_BODY()

protected:
    virtual void BeginPlay() override;

    void TestDelay() const;
};
