// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/MHMCharacter.h"
#include "Core/Interfaces/MHMInteract.h"
#include "MHMAnimalCharacter.generated.h"

class UBoxComponent;
class UMHMInteractWidgetComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMAnimalCharacter final : public AMHMCharacter, public IMHMInteract
{
    GENERATED_BODY()

public:
    explicit AMHMAnimalCharacter(const FObjectInitializer& ObjInit);

    virtual void Interact(AActor* OtherActor) override final;
    virtual void OnEnter() override;
    virtual void OnLeave() override;

protected:
    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UBoxComponent* BlockCollision;

    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UMHMInteractWidgetComponent* InteractWidgetComponent;

    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UAudioComponent* AudioComponent;

    virtual void Dead() override;
};
