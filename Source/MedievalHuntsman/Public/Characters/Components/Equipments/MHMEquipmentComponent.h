// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Interfaces/MHMEquipment.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMEquipmentComponent.generated.h"

class USceneComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMEquipmentComponent : public UMHMActorComponent, public IMHMEquipment
{
    GENERATED_BODY()

public:
    virtual void ToggleEquip(const FName& RowName) override;
    virtual FName GetEquippedItemRowName() const override;
    void SetEquippedSceneComponent(USceneComponent* InEquippedSceneComponent);

protected:
    virtual void Equip(const FName& RowName);
    virtual void UnEquip();
    void AttachActorToSceneComponent(USceneComponent* InEquippedSceneComponent = nullptr) const;
    bool IsEquipped() const;
    AActor* GetEquippedActor() const;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TSubclassOf<AActor> EquippedActorClass;

    UPROPERTY()
    AActor* EquippedActor;

    UPROPERTY()
    USceneComponent* EquippedSceneComponent;

    FName EquippedItemRowName;
};
