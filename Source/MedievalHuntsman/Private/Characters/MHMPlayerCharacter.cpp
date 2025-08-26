// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/MHMPlayerCharacter.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "Characters/Components/Camera/MHMCameraComponent.h"
#include "Characters/Components/Camera/MHMCameraShakeSourceComponent.h"
#include "Characters/Components/Equipments/MHMBowEquipmentComponent.h"
#include "Characters/Components/MHMInteractComponent.h"
#include "Characters/Components/MHMStaminaComponent.h"
#include "Core/Interfaces/MHMInteract.h"

void AMHMPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(InteractComponent);
    InteractComponent->Start(CameraComponent);
}

AMHMPlayerCharacter::AMHMPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    StaminaComponent = CreateDefaultSubobject<UMHMStaminaComponent>(TEXT("StaminaComponent"));
    IMHMMovement* Movement = Cast<IMHMMovement>(GetCharacterMovement());
    check(Movement);
    Movement->SetStamina(StaminaComponent);

    CameraComponent = CreateDefaultSubobject<UMHMCameraComponent>(TEXT("CameraComponent"));
    check(CameraComponent);
    CameraComponent->bUsePawnControlRotation = true;
    CameraComponent->SetStamina(StaminaComponent);
    CameraComponent->SetupAttachment(GetMesh());

    CameraShakeSourceComponent =
        CreateDefaultSubobject<UMHMCameraShakeSourceComponent>(TEXT("CameraShakeSourceComponent"));
    check(CameraShakeSourceComponent);
    CameraShakeSourceComponent->SetStamina(StaminaComponent);
    CameraShakeSourceComponent->SetupAttachment(GetRootComponent());
    
    InteractComponent = CreateDefaultSubobject<UMHMInteractComponent>(TEXT("InteractComponent"));
    check(InteractComponent);
    InteractComponent->OnEntered.AddUObject(this, &ThisClass::OnEnteredInteractingActor);
    InteractComponent->OnLeft.AddUObject(this, &ThisClass::OnLeftInteractingActor);

    BowSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BowSceneComponent"));
    check(BowSceneComponent);
    BowSceneComponent->SetupAttachment(GetMesh());

    BowCombatSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BowCombatSceneComponent"));
    check(BowCombatSceneComponent);
    BowCombatSceneComponent->SetupAttachment(CameraComponent);

    BowEquipmentComponent = CreateDefaultSubobject<UMHMBowEquipmentComponent>(TEXT("BowEquipmentComponent"));
    check(BowEquipmentComponent);
    BowEquipmentComponent->SetStamina(StaminaComponent);
    BowEquipmentComponent->SetCameraShakeSource(CameraShakeSourceComponent);
    BowEquipmentComponent->SetEquippedSceneComponent(BowSceneComponent);
    BowEquipmentComponent->SetCombatEquippedSceneComponent(BowCombatSceneComponent);
}

void AMHMPlayerCharacter::OnEnteredInteractingActor(AActor* InteractingActor)
{
    IMHMInteract* Interact = Cast<IMHMInteract>(InteractingActor);
    if (Interact)
    {
        Interact->OnEnter();
    }
}

void AMHMPlayerCharacter::OnLeftInteractingActor(AActor* InteractingActor)
{
    IMHMInteract* Interact = Cast<IMHMInteract>(InteractingActor);
    if (Interact)
    {
        Interact->OnLeave();
    }
}

void AMHMPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(MovementAction);
    check(LookingAction);
    check(JumpAction);
    check(SprintingAction);
    check(InteractAction);
    check(ToggleCombatAction);
    check(ChargeAction);
    check(FireAction);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    check(EnhancedInputComponent);
    EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
    EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
    EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
    EnhancedInputComponent->BindAction(SprintingAction, ETriggerEvent::Started, this, &ThisClass::StartSprinting);
    EnhancedInputComponent->BindAction(SprintingAction, ETriggerEvent::Completed, this, &ThisClass::StopSprinting);
    EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ThisClass::Interact);
    EnhancedInputComponent->BindAction(ToggleCombatAction, ETriggerEvent::Started, BowEquipmentComponent,
                                       &UMHMBowEquipmentComponent::ToggleCombatMode);
    EnhancedInputComponent->BindAction(ChargeAction, ETriggerEvent::Started, BowEquipmentComponent,
                                       &UMHMBowEquipmentComponent::StartCharge);
    EnhancedInputComponent->BindAction(ChargeAction, ETriggerEvent::Completed, BowEquipmentComponent,
                                       &UMHMBowEquipmentComponent::StopCharge);
    EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, BowEquipmentComponent,
                                       &UMHMBowEquipmentComponent::Fire);
}

void AMHMPlayerCharacter::Move(const FInputActionValue& ActionValue)
{
    if (!FMath::IsNearlyZero(ActionValue.GetMagnitude()) && CanMove())
    {
        AddMovementInput(GetActorForwardVector(), ActionValue[1]);
        AddMovementInput(GetActorRightVector(), ActionValue[0]);
    }
}

void AMHMPlayerCharacter::Look(const FInputActionValue& ActionValue)
{
    if (!FMath::IsNearlyZero(ActionValue.GetMagnitude()) && CanMove())
    {
        AddControllerPitchInput(ActionValue[1]);
        AddControllerYawInput(ActionValue[0]);
    }
}

void AMHMPlayerCharacter::AddControllerPitchInput(const float value)
{
    if (CanMove())
    {
        Super::AddControllerPitchInput(value);
    }
}

void AMHMPlayerCharacter::AddControllerYawInput(const float value)
{
    if (CanMove())
    {
        Super::AddControllerYawInput(value);
    }
}

void AMHMPlayerCharacter::SetMovementType(const EMHMMovementType& MovementType)
{
    IMHMMovement* Movement = Cast<IMHMMovement>(GetCharacterMovement());
    check(Movement);
    Movement->SetMovementType(MovementType);
}

void AMHMPlayerCharacter::StartSprinting()
{
    SetMovementType(EMHMMovementType::Sprinting);
}

void AMHMPlayerCharacter::StopSprinting()
{
    SetMovementType(EMHMMovementType::Running);
}

void AMHMPlayerCharacter::Interact()
{ 
    check(InteractComponent);
    IMHMInteract* Interact = Cast<IMHMInteract>(InteractComponent->GetInteractingActor());
    if (Interact)
    {
        Interact->Interact(this);
    }
}
