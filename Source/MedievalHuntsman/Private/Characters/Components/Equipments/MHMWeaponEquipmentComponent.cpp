// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/Equipments/MHMWeaponEquipmentComponent.h"

void UMHMWeaponEquipmentComponent::ToggleCombatMode()
{
    if (IsEquipped())
    {
        bIsCombatMode ? StopCombatMode() : StartCombatMode();
    }
}

void UMHMWeaponEquipmentComponent::StopCombatMode()
{
    bIsCombatMode = false;
    AttachActorToSceneComponent();
}

void UMHMWeaponEquipmentComponent::StartCombatMode()
{
    bIsCombatMode = true;
    AttachActorToSceneComponent(CombatEquippedSceneComponent);
}

bool UMHMWeaponEquipmentComponent::IsCombatMode() const
{
    return bIsCombatMode;
}

void UMHMWeaponEquipmentComponent::SetCombatEquippedSceneComponent(USceneComponent* InCombatEquippedSceneComponent)
{
    CombatEquippedSceneComponent = InCombatEquippedSceneComponent;
}

void UMHMWeaponEquipmentComponent::UnEquip()
{
    Super::UnEquip();
    StopCombatMode();
}
