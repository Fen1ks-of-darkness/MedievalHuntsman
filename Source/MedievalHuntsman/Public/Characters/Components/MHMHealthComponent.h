// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDead);

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMHealthComponent final : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    FOnDead OnDead;

    virtual void BeginPlay() override;
    void AddHealth(const float AddHealth);
    void ReduceHealth(const float ReduceHealth);
    bool IsDead();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    float MaxHealth = 100.0f;

    float CurrentHealth = MaxHealth;
    bool bIsDead = false;

    void SetCurrentHealth(const float InCurrentHealth);
};
