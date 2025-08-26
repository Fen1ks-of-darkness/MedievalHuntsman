// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/MHMInteract.h"
#include "WorldObjects/MHMWorldObject.h"
#include "MHMInteractableObject.generated.h"

class UMHMInteractWidgetComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMInteractableObject : public AMHMWorldObject, public IMHMInteract
{
    GENERATED_BODY()

public:
    AMHMInteractableObject();

    virtual void Interact(AActor* OtherActor) override final;
    virtual void OnEnter() override;
    virtual void OnLeave() override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UMHMInteractWidgetComponent* InteractWidgetComponent;

    virtual void BeginPlay() override;
    virtual FText GetObjectName() const;
    virtual bool CanInteract() const;
    virtual void DoInteract(AActor* OtherActor);
};
