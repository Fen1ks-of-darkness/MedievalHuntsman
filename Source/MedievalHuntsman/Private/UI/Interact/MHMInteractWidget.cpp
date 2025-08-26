// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Interact/MHMInteractWidget.h"
#include "Components/TextBlock.h"
#include "InputMappingContext.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Settings/MHMGameSettings.h"

void UMHMInteractWidget::NativePreConstruct()
{
    Super::NativePreConstruct();

    if (InteractKeyTextBlock)
    {
        const UMHMGameSettings* GameSettings = GetDefault<UMHMGameSettings>();
        check(GameSettings);
        const UInputMappingContext* InputMappingContext = GameSettings->InputMappingContext.LoadSynchronous();
        InteractKeyTextBlock->SetText(FMHMHelperFunctions::GetDisplayNameByAction(InputMappingContext, InteractAction));
    }
}

void UMHMInteractWidget::SetObjectName(const FText& ObjectName) const
{
    check(ObjectNameTextBlock);
    ObjectNameTextBlock->SetText(ObjectName);
}

void UMHMInteractWidget::SetInteractText(const FText& InteractText) const
{
    check(InteractTextTextBlock);
    InteractTextTextBlock->SetText(InteractText);
}
