// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Interfaces/MHMPlayerInfo.h"
#include "Characters/MHMCharacter.h"
#include "MHMPlayerCharacter.generated.h"

class UInputAction;
class UMHMBowEquipmentComponent;
class UMHMCameraComponent;
class UMHMCameraShakeSourceComponent;
class UMHMInteractComponent;
class UMHMStaminaComponent;
class UInputComponent;
struct FInputActionValue;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMPlayerCharacter final : public AMHMCharacter, public IMHMPlayerInfo
{
    GENERATED_BODY()

public:
    AMHMPlayerCharacter(const FObjectInitializer& ObjInit);
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void AddControllerPitchInput(const float value) override;
    virtual void AddControllerYawInput(const float value) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UMHMCameraComponent* CameraComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMCameraShakeSourceComponent* CameraShakeSourceComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMInteractComponent* InteractComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMStaminaComponent* StaminaComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMBowEquipmentComponent* BowEquipmentComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
    USceneComponent* BowSceneComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    USceneComponent* BowCombatSceneComponent;

    virtual void BeginPlay() override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* MovementAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* LookingAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* JumpAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* SprintingAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* InteractAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* ToggleCombatAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* ChargeAction;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Input")
    UInputAction* FireAction;

    void OnEnteredInteractingActor(AActor* InteractingActor);
    void OnLeftInteractingActor(AActor* InteractingActor);
    void Move(const FInputActionValue& ActionValue);
    void Look(const FInputActionValue& ActionValue);
    void SetMovementType(const EMHMMovementType& MovementType);
    void StartSprinting();
    void StopSprinting();
    void Interact();
};
