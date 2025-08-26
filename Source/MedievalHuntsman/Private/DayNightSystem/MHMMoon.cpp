// Copyright Epic Games, Inc. All Rights Reserved.

#include "DayNightSystem/MHMMoon.h"

AMHMMoon::AMHMMoon() : Super()
{
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
    SetRootComponent(SceneComponent);

    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    check(StaticMeshComponent);
    StaticMeshComponent->SetupAttachment(SceneComponent);
}

void AMHMMoon::SetPhase(const float Phase) const
{
    check(Phase <= 1.0f);
    check(Phase >= -1.0f);
    check(StaticMeshComponent);

    StaticMeshComponent->SetScalarParameterValueOnMaterials(PhaseParameterName, Phase);
}
