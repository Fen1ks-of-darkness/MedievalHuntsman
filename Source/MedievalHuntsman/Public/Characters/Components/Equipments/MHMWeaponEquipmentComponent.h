// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/Equipments/MHMEquipmentComponent.h"
#include "MHMWeaponEquipmentComponent.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMWeaponEquipmentComponent : public UMHMEquipmentComponent
{
    GENERATED_BODY()

public:
    void ToggleCombatMode();
    bool IsCombatMode() const;
    void SetCombatEquippedSceneComponent(USceneComponent* InCombatEquippedSceneComponent);

protected:
    virtual void UnEquip() override;

private:
    UPROPERTY()
    USceneComponent* CombatEquippedSceneComponent;

    bool bIsCombatMode;

    void StartCombatMode();
    void StopCombatMode();
};
