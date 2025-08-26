// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "MHMInteractWidgetComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMInteractWidgetComponent final : public UWidgetComponent
{
    GENERATED_BODY()

public:
    UMHMInteractWidgetComponent();

    virtual void BeginPlay() override;
    void SetObjectName(const FText& InObjectName);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FText ObjectName;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    FText InteractText;

    void UpdateWidgetObjectData() const;
};
