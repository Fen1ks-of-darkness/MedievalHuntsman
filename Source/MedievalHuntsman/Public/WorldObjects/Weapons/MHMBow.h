// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/Interfaces/MHMBowFighting.h"
#include "WorldObjects/Weapons/MHMWeapon.h"
#include "MHMBow.generated.h"

class AMHMArrow;
class IMHMInventory;
class UAudioComponent;
class UTimelineComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMBow final : public AMHMWeapon, public IMHMBowFighting
{
    GENERATED_BODY()

public:
    AMHMBow();

    virtual void StartCharge() override;
    virtual void StopCharge() override;
    virtual void Fire() override;
    virtual float GetCharge() const override;

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UAudioComponent* ChargeAudioComponent;

    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings|Main")
    UCurveFloat* ChargeCurve;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Arrow")
    TSubclassOf<AMHMArrow> ArrowClass;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Arrow")
    FName ArrowSocketName;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Arrow")
    FName ArrowRowName;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Sounds")
    USoundBase* FireSound;

    UPROPERTY()
    AMHMArrow* Arrow;

    UPROPERTY()
    UTimelineComponent* ChargeTimeLine;

    UFUNCTION()
    void ProgressCharge(const float value);

    IMHMInventory* OwnerInventory;
    FTimerHandle TimerHandle;
    float Charge = 0.0f;
};
