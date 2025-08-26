// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MHMMoon.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMMoon final : public AActor
{
    GENERATED_BODY()

public:
    AMHMMoon();
    void SetPhase(const float Phase) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* SceneComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

private:
    UPROPERTY(EditDefaultsOnly)
    FName PhaseParameterName;
};
