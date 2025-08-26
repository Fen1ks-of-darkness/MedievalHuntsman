// Copyright Epic Games, Inc. All Rights Reserved.

#include "Core/Components/MHMInteractWidgetComponent.h"
#include "Core/Interfaces/MHMInteractData.h"

UMHMInteractWidgetComponent::UMHMInteractWidgetComponent() : Super()
{
    SetWidgetSpace(EWidgetSpace::Screen);
    SetDrawAtDesiredSize(true);
    SetVisibility(false);
}

void UMHMInteractWidgetComponent::UpdateWidgetObjectData() const
{
    const IMHMInteractData* InteractData = Cast<IMHMInteractData>(GetWidget());
    check(InteractData);
    InteractData->SetObjectName(ObjectName);
    InteractData->SetInteractText(InteractText);
}

void UMHMInteractWidgetComponent::BeginPlay()
{
    Super::BeginPlay();
    UpdateWidgetObjectData();
}

void UMHMInteractWidgetComponent::SetObjectName(const FText& InObjectName)
{
    ObjectName = InObjectName;
    UpdateWidgetObjectData();
}
