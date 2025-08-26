// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/MHMInteractableObject.h"
#include "Core/Components/MHMInteractWidgetComponent.h"

AMHMInteractableObject::AMHMInteractableObject() : Super()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    SetRootComponent(StaticMeshComponent);

    InteractWidgetComponent = CreateDefaultSubobject<UMHMInteractWidgetComponent>(TEXT("InteractWidgetComponent"));
    check(InteractWidgetComponent);
    InteractWidgetComponent->SetupAttachment(StaticMeshComponent);
}

void AMHMInteractableObject::Interact(AActor* OtherActor)
{
    if (CanInteract())
    {
        DoInteract(OtherActor);
    }
}

void AMHMInteractableObject::BeginPlay()
{
    Super::BeginPlay();
    check(InteractWidgetComponent);
    InteractWidgetComponent->SetObjectName(GetObjectName());
}

FText AMHMInteractableObject::GetObjectName() const
{
    return FText();
}

bool AMHMInteractableObject::CanInteract() const
{
    return true;
}

void AMHMInteractableObject::DoInteract(AActor* OtherActor) {}

void AMHMInteractableObject::OnEnter()
{
    if (CanInteract())
    {
        check(InteractWidgetComponent);
        InteractWidgetComponent->SetVisibility(true);
    }
}

void AMHMInteractableObject::OnLeave()
{
    if (CanInteract())
    {
        check(InteractWidgetComponent);
        InteractWidgetComponent->SetVisibility(false);
    }
}
