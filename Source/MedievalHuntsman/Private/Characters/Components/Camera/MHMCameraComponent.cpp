// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/Camera/MHMCameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Characters/Interfaces/MHMStamina.h"

void UMHMCameraComponent::BeginPlay()
{
    Super::BeginPlay();
    GammaWithNormalStamina = PostProcessSettings.ColorGamma;
    BloomWithNormalStamina = PostProcessSettings.BloomIntensity;
    VignetteWithNormalStamina = PostProcessSettings.VignetteIntensity;
}

void UMHMCameraComponent::SetStamina(IMHMStamina* InStamina)
{
    Stamina = InStamina;
    check(Stamina);
    Stamina->OnChangedStamina().AddUObject(this, &ThisClass::StaminaEffect);
}

void UMHMCameraComponent::StaminaEffect()
{
    check(Stamina);
    const float CurrentStamina = Stamina->GetCurrentStamina();
    if (CurrentStamina < StartValueForStaminaEffect)
    {
        const float Alpha = UKismetMathLibrary::MapRangeClamped(CurrentStamina, 0, StartValueForStaminaEffect, 0, 1);
        const FVector4d GammaValue = FMath::Lerp(GammaWithMinStamina, GammaWithNormalStamina, Alpha);
        const float BloomIntensityValue = FMath::Lerp(BloomIntensityWithMinStamina, BloomWithNormalStamina, Alpha);
        const float VignetteIntensityValue =
            FMath::Lerp(VignetteIntensityWithMinStamina, VignetteWithNormalStamina, Alpha);
        PostProcessSettings.ColorGamma = GammaValue;
        PostProcessSettings.BloomIntensity = BloomIntensityValue;
        PostProcessSettings.VignetteIntensity = VignetteIntensityValue;
    }
}
