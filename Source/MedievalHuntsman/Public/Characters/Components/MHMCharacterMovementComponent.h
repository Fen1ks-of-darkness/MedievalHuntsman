// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "MHMCharacterMovementComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMCharacterMovementComponent final : public UCharacterMovementComponent,
                                                                  public IMHMMovement
{
    GENERATED_BODY()
public:
    virtual void TickComponent(float DeltaTime, enum ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;
    virtual float GetMaxSpeed() const override;
    virtual bool DoJump(bool bReplayingMoves, float DeltaTime) override;
    virtual bool IsInAir() const override;
    virtual void SetStamina(IMHMStamina* InStamina) override;
    virtual void SetMovementType(const EMHMMovementType& InMovementType) override;
    virtual void SetCanMove() override;
    virtual void ResetCanMove() override;
    virtual bool CanMove() const override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<EMHMMovementType, float> Speeds{
        {EMHMMovementType::Walking, 300.0f},
        {EMHMMovementType::Running, 600.0f},
        {EMHMMovementType::Sprinting, 900.0f},
    };

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<EMHMMovementType, float> StaminaUsagePerSecond{
        {EMHMMovementType::Walking, 0.0f},
        {EMHMMovementType::Running, 0.0f},
        {EMHMMovementType::Sprinting, 15.0f},
    };

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    float StaminaUsagePerJump = 10.0f;

    IMHMStamina* Stamina;
    EMHMMovementType MovementType = EMHMMovementType::Running;
    bool bCanMove = true;

    void RanOutStamina();
};
