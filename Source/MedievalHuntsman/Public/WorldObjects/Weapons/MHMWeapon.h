// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/MHMRowName.h"
#include "WorldObjects/MHMWorldObject.h"
#include "MHMWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMWeapon : public AMHMWorldObject, public IMHMRowName
{
    GENERATED_BODY()

public:
    AMHMWeapon();

    virtual void SetRowName(const FName& InRowName) override;
    virtual FName GetRowName() const override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    USkeletalMeshComponent* SkeletalMeshComponent;

private:
    FName RowName;
};
