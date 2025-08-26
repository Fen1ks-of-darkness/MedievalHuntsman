// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/Camera/MHMCameraShakeSourceComponent.h"
#include "Characters/Interfaces/MHMStamina.h"

void UMHMCameraShakeSourceComponent::StartShaking()
{
    check(Stamina);
    Stamina->OnChangedStamina().AddUObject(this, &ThisClass::StaminaEffect);
    StaminaEffect();
}

void UMHMCameraShakeSourceComponent::StaminaEffect()
{
    const float Scale = GetScale();
    if (FMath::Abs(LastScale - Scale) > Threshold)
    {
        StartCameraShake(CameraShake, Scale);
        LastScale = Scale;
    }
}

float UMHMCameraShakeSourceComponent::GetScale() const
{
    check(Stamina);
    return 1 - Stamina->GetPercentStamina();
}

void UMHMCameraShakeSourceComponent::StopShaking()
{
    check(Stamina);
    Stamina->OnChangedStamina().RemoveAll(this);
    StopAllCameraShakes();
    LastScale = 0.0f;
}

void UMHMCameraShakeSourceComponent::SetStamina(IMHMStamina* InStamina)
{
    Stamina = InStamina;
}
