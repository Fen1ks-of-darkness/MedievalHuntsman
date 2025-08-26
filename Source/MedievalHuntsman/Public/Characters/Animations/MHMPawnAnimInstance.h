// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "MHMPawnAnimInstance.generated.h"

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API UMHMPawnAnimInstance final : public UAnimInstance
{
    GENERATED_BODY()

public:
    virtual void NativeInitializeAnimation() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Speed = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    float Direction = 0.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bIsFalling = false;

private:
    UPROPERTY()
    APawn* Pawn;

    IMHMMovement* Movement;
};
