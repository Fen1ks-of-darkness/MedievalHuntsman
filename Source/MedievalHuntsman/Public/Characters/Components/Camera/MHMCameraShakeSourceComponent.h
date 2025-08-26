// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraShakeSourceComponent.h"
#include "Characters/Interfaces/MHMCameraShakeSource.h"
#include "MHMCameraShakeSourceComponent.generated.h"

class IMHMStamina;

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMCameraShakeSourceComponent final : public UCameraShakeSourceComponent,
                                                                  public IMHMCameraShakeSource
{
    GENERATED_BODY()
public:
    virtual void StartShaking() override;
    virtual void StopShaking() override;
    void SetStamina(IMHMStamina* InStamina);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Setting",
              meta = (ClampMin = "0.05", UIMin = "0.05", ClampMax = "1.0", UIMax = "1.0"))
    float Threshold = 0.1f;

    void StaminaEffect();
    float GetScale() const;
    float LastScale = 0.0f;

    IMHMStamina* Stamina;
};
