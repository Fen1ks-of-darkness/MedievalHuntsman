// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Components/AI/MHMAiComponent.h"
#include "MHMEscapeAiComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnEscaped);

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMEscapeAiComponent final : public UMHMAiComponent
{
    GENERATED_BODY()

public:
    FOnEscaped OnEscaped;

    virtual void Start(AAIController* InAIController) override;
    virtual void Stop() override;
    void SetEnemy(const AActor* InEnemy);
    void DamageHasBeenReceived();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", unit = "Centimeters"))
    float SafeDistance = 3000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", unit = "Centimeters"))
    float SafeDistanceAfterHit = 8000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", unit = "Centimeters"))
    float DistanceForEscape = 1000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", unit = "Centimeters"))
    float Radius = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0.1", UIMin = "0.1", unit = "Seconds"))
    float TimerRate = 0.5f;

    UPROPERTY()
    const AActor* Enemy;

    FTimerHandle TimerHandle;
    bool bDamageHasBeenReceived = false;

    void GoToNextLocation();
    float GetCurrentSafeDistance() const;
    FVector GetNextLocation() const;
};
