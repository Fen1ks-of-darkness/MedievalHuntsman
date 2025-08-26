// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Core/Interfaces/MHMRowName.h"
#include "WorldObjects/interactableObjects/MHMInteractableObject.h"
#include "MHMItem.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMItem : public AMHMInteractableObject, public IMHMRowName
{
    GENERATED_BODY()

public:
    virtual void OnConstruction(const FTransform& Transform) override;
    virtual void SetRowName(const FName& InRowName) override;
    virtual FName GetRowName() const override;

protected:
    virtual FText GetObjectName() const;
    virtual void DoInteract(AActor* OtherActor) override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings")
    FDataTableRowHandle ItemRow;

    void InitMesh();
};
