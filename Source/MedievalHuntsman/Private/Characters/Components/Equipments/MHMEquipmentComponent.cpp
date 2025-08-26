// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/Equipments/MHMEquipmentComponent.h"
#include "Core/Interfaces/MHMRowName.h"

void UMHMEquipmentComponent::ToggleEquip(const FName& RowName)
{
    const bool bIsNeedEquip = !RowName.IsEqual(EquippedItemRowName);
    UnEquip();
    if (bIsNeedEquip)
    {
        Equip(RowName);
    }
}

void UMHMEquipmentComponent::UnEquip()
{
    if (EquippedActor)
    {
        EquippedActor->Destroy();
    }
    EquippedItemRowName = NAME_None;
}

void UMHMEquipmentComponent::Equip(const FName& RowName)
{
    check(GetWorld());
    EquippedActor = GetWorld()->SpawnActorDeferred<AActor>(EquippedActorClass, FTransform::Identity, GetOwner(),
                                                           nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
    if (EquippedActor)
    {
        EquippedActor->FinishSpawning(FTransform::Identity);
        AttachActorToSceneComponent();
        IMHMRowName* ItemRowName = Cast<IMHMRowName>(EquippedActor);
        check(ItemRowName);
        ItemRowName->SetRowName(RowName);
        EquippedItemRowName = RowName;
    }
}

void UMHMEquipmentComponent::AttachActorToSceneComponent(USceneComponent* InEquippedSceneComponent) const
{
    if (EquippedActor)
    {
        const FAttachmentTransformRules AttachmentRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
        EquippedActor->AttachToComponent(InEquippedSceneComponent ? InEquippedSceneComponent : EquippedSceneComponent,
                                         AttachmentRules);
    }
}

FName UMHMEquipmentComponent::GetEquippedItemRowName() const
{
    return EquippedItemRowName;
}

void UMHMEquipmentComponent::SetEquippedSceneComponent(USceneComponent* InEquippedSceneComponent)
{
    EquippedSceneComponent = InEquippedSceneComponent;
}

bool UMHMEquipmentComponent::IsEquipped() const
{
    return !EquippedItemRowName.IsNone();
}

AActor* UMHMEquipmentComponent::GetEquippedActor() const
{
    return EquippedActor;
}
