// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/HUD/MHMGameHUDWidget.h"
#include "Characters/Interfaces/MHMHUDPlayerController.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Interfaces/MHMInventory.h"
#include "UI/Inventory/MHMInventoryWidget.h"
#include "UI/Inventory/Messages/MHMInventoryMessagesWidget.h"
#include "UI/Inventory/Strategies/MHMPlayerInventoryStrategy.h"
#include "UI/Pause/MHMPauseWidget.h"

void UMHMGameHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    if (!GetOwningPlayerPawn())
    {
        Hide();
        return;
    }

    check(PlayerInventoryWidget);
    check(InventoryMessagesWidget);
    check(PlayerInventoryStrategyClass);
    check(PauseWidget);

    IMHMInventory* PlayerInventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(GetOwningPlayerPawn());
    check(PlayerInventory);
    PlayerInventoryWidget->SetInventory(PlayerInventory);

    UMHMPlayerInventoryStrategy* PlayerInventoryStrategy =
        NewObject<UMHMPlayerInventoryStrategy>(this, PlayerInventoryStrategyClass);
    PlayerInventoryStrategy->SetPlayer(GetOwningPlayerPawn());
    PlayerInventoryWidget->SetStrategy(PlayerInventoryStrategy);

    PlayerInventoryWidget->Hide();
    InventoryMessagesWidget->SetInventory(PlayerInventory);

    IMHMHUDPlayerController* HUDPlayerController = Cast<IMHMHUDPlayerController>(GetOwningPlayer());
    check(HUDPlayerController);
    HUDPlayerController->OnToggleInventoryWidget().AddUObject(PlayerInventoryWidget, &ThisClass::Toggle);
    HUDPlayerController->OnTogglePauseWidget().AddUObject(PauseWidget, &ThisClass::Toggle);

    PauseWidget->Hide();
}
