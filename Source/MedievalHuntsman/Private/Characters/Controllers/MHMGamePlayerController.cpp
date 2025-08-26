// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Controllers/MHMGamePlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Settings/MHMGameSettings.h"

void AMHMGamePlayerController::BeginPlay()
{
    Super::BeginPlay();
    UpdateInputMode();
        
    UEnhancedInputLocalPlayerSubsystem* EnhancedInput =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (EnhancedInput)
    {
        EnhancedInput->ClearAllMappings();

        const UMHMGameSettings* GameSettings = GetDefault<UMHMGameSettings>();
        check(GameSettings);
        EnhancedInput->AddMappingContext(GameSettings->InputMappingContext.LoadSynchronous(), 0);
    }
}

void AMHMGamePlayerController::ContinueGame()
{
    TogglePauseWidget();
}

void AMHMGamePlayerController::TogglePauseWidget()
{
    bIsPauseShown = !bIsPauseShown;
    SetPause(bIsPauseShown);
    UpdateInputMode();
    OnTogglePauseWidgetEvent.Broadcast();
}

void AMHMGamePlayerController::UpdateInputMode()
{
    bShowMouseCursor = bIsInventoryShown || bIsPauseShown;
    if (bShowMouseCursor)
    {
        SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
    }
}

void AMHMGamePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    check(InventoryAction);
    check(PauseAction);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    check(EnhancedInputComponent);
    EnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Started, this,
                                       &ThisClass::ToggleInventoryWidget);
    EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ThisClass::TogglePauseWidget);
}

void AMHMGamePlayerController::ToggleInventoryWidget()
{
    bIsInventoryShown = !bIsInventoryShown;
    IMHMMovement* Movement = FMHMHelperFunctions::GetComponentByInterface<IMHMMovement>(GetPawn());
    check(Movement);
    bIsInventoryShown ? Movement->ResetCanMove() : Movement->SetCanMove();
    UpdateInputMode();
    OnToggleInventoryWidgetEvent.Broadcast();
}

FOnToggleWidget& AMHMGamePlayerController::OnToggleInventoryWidget()
{
    return OnToggleInventoryWidgetEvent;
}

FOnToggleWidget& AMHMGamePlayerController::OnTogglePauseWidget()
{
    return OnTogglePauseWidgetEvent;
}
