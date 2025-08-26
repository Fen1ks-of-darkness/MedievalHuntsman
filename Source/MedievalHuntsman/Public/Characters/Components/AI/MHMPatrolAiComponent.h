// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/MHMAiComponent.h"
#include "MHMPatrolAiComponent.generated.h"

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMPatrolAiComponent final : public UMHMAiComponent
{
    GENERATED_BODY()

public:
    virtual void Start(AAIController* InAIController) override;
    virtual void Stop() override;
    virtual void OnMoveCompleted(const bool bIsSuccess) override;
    void SetStartLocation(const FVector& InStartLocation);

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Untits = "Centimeters"))
    float Radius = 1000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Untits = "Seconds"))
    float DelayAfterSuccess = 2.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0.2", UIMin = "0.2", Untits = "Seconds"))
    float DelayAfterFail = 0.2f;

    FTimerHandle TimerHandle;
    FVector StartLocation;

    void GoToNextLocation() const;
};
