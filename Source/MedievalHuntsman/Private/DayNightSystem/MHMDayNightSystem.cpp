// Copyright Epic Games, Inc. All Rights Reserved.

#include "DayNightSystem/MHMDayNightSystem.h"
#include "Engine/DirectionalLight.h"
#include "DayNightSystem/MHMMoon.h"

void AMHMDayNightSystem::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    Time = (Day - 1) * SecondsInDay + Hour * SecondsInHour + Minute * SecondsInMinute + Second;
    UpdateAll();
}

void AMHMDayNightSystem::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::IncreaseTime, GetTimerRate(), true);
}

void AMHMDayNightSystem::IncreaseTime()
{
    Time += TimeSpeed * GetTimerRate();
    UpdateAll();
}

void AMHMDayNightSystem::UpdateAll() const
{
    UpdateDirectionalLight();
    UpdateMoon();
}

void AMHMDayNightSystem::UpdateDirectionalLight() const
{
    if (DirectionalLight && DirectionalLightPitchCurve)
    {
        UpdateRotation(DirectionalLight, DirectionalLightPitchCurve);
    }
}

void AMHMDayNightSystem::UpdateRotation(AActor* Actor, const UCurveFloat* Curve) const
{
    check(Actor);
    check(Curve);

    const float PitchInRadians = FMath::DegreesToRadians(Curve->GetFloatValue(GetHour()));
    const FQuat DirectionalLightRotation = FQuat(FVector::RightVector, PitchInRadians);
    Actor->SetActorRotation(DirectionalLightRotation);
}

void AMHMDayNightSystem::UpdateMoon() const
{
    if (Moon && MoonPitchCurve && MoonPhaseCurve)
    {
        UpdateRotation(Moon, MoonPitchCurve);
        Moon->SetPhase(MoonPhaseCurve->GetFloatValue(FMath::RoundToInt32(GetDay()) % 28));
    }
}

float AMHMDayNightSystem::GetDay() const
{
    return Time / SecondsInDay + 1;
}

float AMHMDayNightSystem::GetHour() const
{
    return static_cast<float>(FMath::RoundToInt32(Time) % SecondsInDay) / SecondsInHour;
}

float AMHMDayNightSystem::GetTimerRate() const
{
    check(TimeSpeed > 0);
    return FMath::Max(1 / TimeSpeed, MinTimerRate);
}