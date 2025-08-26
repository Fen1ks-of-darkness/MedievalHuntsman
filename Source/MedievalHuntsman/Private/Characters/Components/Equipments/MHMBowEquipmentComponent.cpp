// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/Equipments/MHMBowEquipmentComponent.h"
#include "Characters/Interfaces/MHMCameraShakeSource.h"
#include "Characters/Interfaces/MHMStamina.h"

UMHMBowEquipmentComponent::UMHMBowEquipmentComponent() : Super()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UMHMBowEquipmentComponent::BeginPlay()
{
    Super::BeginPlay();
    SetComponentTickEnabled(false);
}

void UMHMBowEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    check(Stamina);
    Stamina->UseStamina(StaminaUsageWhileChargingPerSecond * DeltaTime);
}

void UMHMBowEquipmentComponent::StartCharge()
{
    if (GetBowFighting())
    {
        check(CameraShakeSource);
        GetBowFighting()->StartCharge();
        CameraShakeSource->StartShaking();
        SetComponentTickEnabled(true);
    }
}

IMHMBowFighting* UMHMBowEquipmentComponent::GetBowFighting() const
{
    return Cast<IMHMBowFighting>(GetEquippedActor());
}

void UMHMBowEquipmentComponent::StopCharge()
{
    if (GetBowFighting())
    {
        check(CameraShakeSource);
        GetBowFighting()->StopCharge();
        CameraShakeSource->StopShaking();
        SetComponentTickEnabled(false);
    }
}

void UMHMBowEquipmentComponent::Fire()
{
    if (GetBowFighting())
    {
        GetBowFighting()->Fire();
    }
}

float UMHMBowEquipmentComponent::GetCharge() const
{
    if (GetBowFighting())
    {
        return GetBowFighting()->GetCharge();
    }
    return 0.0f;
}

void UMHMBowEquipmentComponent::SetCameraShakeSource(IMHMCameraShakeSource* InCameraShakeSource)
{
    CameraShakeSource = InCameraShakeSource;
}

void UMHMBowEquipmentComponent::SetStamina(IMHMStamina* InStamina)
{
    Stamina = InStamina;
}
