// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Components/MHMHealthComponent.h"

void UMHMHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetCurrentHealth(MaxHealth);
}

void UMHMHealthComponent::SetCurrentHealth(const float InCurrentHealth)
{
    CurrentHealth = FMath::Clamp(InCurrentHealth, 0, MaxHealth);

    if (bIsDead) return;
    if (FMath::IsNearlyZero(CurrentHealth))
    {
        bIsDead = true;
        OnDead.Broadcast();
    }
}

void UMHMHealthComponent::AddHealth(const float AddHealth)
{
    SetCurrentHealth(MaxHealth + AddHealth);
}

void UMHMHealthComponent::ReduceHealth(const float ReduceHealth)
{
    SetCurrentHealth(MaxHealth - ReduceHealth);
}

bool UMHMHealthComponent::IsDead()
{
    return bIsDead;
}
