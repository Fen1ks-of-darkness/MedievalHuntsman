// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldObjects/interactableObjects/Items/MHMItem.h"
#include "MHMArrow.generated.h"

class UProjectileMovementComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMArrow final : public AMHMItem
{
    GENERATED_BODY()
public:
    AMHMArrow();
    void Fire(const float Charge);
    void SetDamageAmount(const float InDamageAmount);

protected:
    UPROPERTY(VisibleAnywhere, Category = "Components")
    UProjectileMovementComponent* ProjectileMovementComponent;

    virtual bool CanInteract() const override;

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings|Speed",
              meta = (ClampMin = "0", UIMin = "0", Units = "CentimetersPerSecond"))
    float MinSpeed = 100.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Speed",
              meta = (ClampMin = "0", UIMin = "0", Units = "CentimetersPerSecond"))
    float MaxSpeed = 5000.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings|Sounds")
    USoundBase* HitSound;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
               FVector NormalImpulse, const FHitResult& Hit);

    float DamageAmount;
};
