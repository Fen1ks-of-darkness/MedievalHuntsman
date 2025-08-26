// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MHMDayNightSystem.generated.h"

class ADirectionalLight;
class AMHMMoon;
class UCurveFloat;

UCLASS()
class MEDIEVALHUNTSMAN_API AMHMDayNightSystem final : public AActor
{
    GENERATED_BODY()

public:
    virtual void OnConstruction(const FTransform& Transform) override;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY(EditInstanceOnly, Category = "Settings|Main", meta = (ClampMin = "1", UIMin = "1"))
    uint32 Day = 1;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Main",
              meta = (ClampMin = "0", UIMin = "0", ClampMax = "23", UIMax = "23"))
    uint32 Hour = 9;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Main",
              meta = (ClampMin = "0", UIMin = "0", ClampMax = "59", UIMax = "59"))
    uint32 Minute = 0;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Main",
              meta = (ClampMin = "0", UIMin = "0", ClampMax = "59", UIMax = "59"))
    uint32 Second = 0;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Main", meta = (ClampMin = "0.1", UIMin = "0.1"))
    float TimeSpeed = 1.0f;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Main", meta = (ClampMin = "0.05", UIMin = "0.05"))
    float MinTimerRate = 0.05f;

    UPROPERTY()
    float Time;

    FTimerHandle TimerHandle;
    const uint32 SecondsInDay = 86400;
    const uint32 SecondsInHour = 3600;
    const uint32 SecondsInMinute = 60;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Objects")
    ADirectionalLight* DirectionalLight;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Objects")
    AMHMMoon* Moon;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Curves")
    UCurveFloat* DirectionalLightPitchCurve;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Curves")
    UCurveFloat* MoonPitchCurve;

    UPROPERTY(EditInstanceOnly, Category = "Settings|Curves")
    UCurveFloat* MoonPhaseCurve;

    void UpdateAll() const;
    void UpdateDirectionalLight() const;
    void UpdateRotation(AActor* Actor, const UCurveFloat* Curve) const;
    void UpdateMoon() const;
    void IncreaseTime();
    float GetDay() const;
    float GetHour() const;
    float GetTimerRate() const;
};
