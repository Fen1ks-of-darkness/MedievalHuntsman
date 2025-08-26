// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "MHMAnimalAiController.generated.h"

class UMHMAiComponent;
class UMHMPatrolAiComponent;
class UMHMEscapeAiComponent;

UCLASS(Abstract)
class MEDIEVALHUNTSMAN_API AMHMAnimalAiController final : public AAIController
{
    GENERATED_BODY()

public:
    AMHMAnimalAiController();

    virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result);

protected:
    UPROPERTY(VisibleAnyWhere, Category = "Components")
    UAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMPatrolAiComponent* PatrolAiComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Components")
    UMHMEscapeAiComponent* EscapeAiComponent;

    virtual void OnPossess(APawn* InPawn) override;

private:
    UFUNCTION()
    void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

    UFUNCTION()
    void PointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
                     class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
                     const class UDamageType* DamageType, AActor* DamageCauser);

    UPROPERTY()
    UMHMAiComponent* CurrentAiComponent;

    void OnEscaped();
    void StartAiComponent(UMHMAiComponent* AiComponent);
};
