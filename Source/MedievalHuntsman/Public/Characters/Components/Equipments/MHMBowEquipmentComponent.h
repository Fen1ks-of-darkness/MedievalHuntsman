// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/Equipments/MHMWeaponEquipmentComponent.h"
#include "Core/Interfaces/MHMBowFighting.h"
#include "MHMBowEquipmentComponent.generated.h"

class IMHMCameraShakeSource;
class IMHMStamina;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMBowEquipmentComponent final : public UMHMWeaponEquipmentComponent, public IMHMBowFighting
{
    GENERATED_BODY()

public:
    UMHMBowEquipmentComponent();
    virtual void BeginPlay() override;
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    virtual void StartCharge() override;
    virtual void StopCharge() override;
    virtual void Fire() override;
    virtual float GetCharge() const override;
    void SetCameraShakeSource(IMHMCameraShakeSource* InCameraShakeSource);
    void SetStamina(IMHMStamina* InStamina);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float StaminaUsageWhileChargingPerSecond = 10.0f;

    IMHMCameraShakeSource* CameraShakeSource;
    IMHMStamina* Stamina;
    IMHMBowFighting* GetBowFighting() const;
};
