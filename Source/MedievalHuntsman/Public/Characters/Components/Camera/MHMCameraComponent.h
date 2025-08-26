// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "MHMCameraComponent.generated.h"

class IMHMStamina;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMCameraComponent : public UCameraComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;
    void SetStamina(IMHMStamina* InStamina);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float StartValueForStaminaEffect = 30.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FVector4d GammaWithMinStamina{0.7f, 0.7f, 0.7f, 0.7f};

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float BloomIntensityWithMinStamina = 3.6f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float VignetteIntensityWithMinStamina = 1.0f;

    IMHMStamina* Stamina;
    FVector4d GammaWithNormalStamina;
    float BloomWithNormalStamina;
    float VignetteWithNormalStamina;

    void StaminaEffect();
};
