// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MHMBowAnimInstance.generated.h"

class IMHMBowFighting;

UCLASS(abstract)
class MEDIEVALHUNTSMAN_API UMHMBowAnimInstance final : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(const float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Charge = 0.0f;

private:
    IMHMBowFighting* BowFighting;
};
