// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Characters/Interfaces/MHMMovement.h"
#include "Core/Interfaces/MHMAddingArrow.h"
#include "MHMCharacter.generated.h"

class UMHMHealthComponent;
class UMHMInventoryComponent;
class UMHMStartingItemsComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMCharacter : public ACharacter, public IMHMAddingArrow
{
    GENERATED_BODY()

public:
    explicit AMHMCharacter(const FObjectInitializer& ObjInit);

    virtual void AddArrow(AActor* Actor) override;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMHealthComponent* HealthComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMInventoryComponent* InventoryComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMStartingItemsComponent* StartingItemsComponent;

    UFUNCTION()
    virtual void PointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
                             class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                             const class UDamageType* DamageType, AActor* DamageCauser);

    virtual void Dead();
    bool CanMove() const;
    TArray<AActor*>& GetAddedArrows();

private:
    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TMap<FName, float> BonesAndDamageMultipliersMatching;

    UPROPERTY()
    TArray<AActor*> AddedArrows;
};
