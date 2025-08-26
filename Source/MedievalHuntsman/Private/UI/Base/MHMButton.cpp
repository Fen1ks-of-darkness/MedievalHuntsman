// Copyright Epic Games, Inc. All Rights Reserved.

#include "UI/Base/MHMButton.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

FOnButtonClickedEvent& UMHMButton::OnClicked() const
{
    check(Button);
    return Button->OnClicked;
}

void UMHMButton::NativePreConstruct()
{
    Super::NativePreConstruct();
    check(TextBlock);
    TextBlock->SetText(TextButton);
}
