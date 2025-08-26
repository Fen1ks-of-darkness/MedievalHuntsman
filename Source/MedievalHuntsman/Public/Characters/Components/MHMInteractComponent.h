// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Core/BaseTypes/MHMActorComponent.h"
#include "MHMInteractComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEntered, AActor*)
DECLARE_MULTICAST_DELEGATE_OneParam(FOnLeft, AActor*)

UCLASS()
class MEDIEVALHUNTSMAN_API UMHMInteractComponent final : public UMHMActorComponent
{
    GENERATED_BODY()

public:
    FOnEntered OnEntered;
    FOnLeft OnLeft;

    void Start(USceneComponent* InSceneComponent);
    AActor* GetInteractingActor() const;

private:
    FTimerHandle TimerHandle;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Seconds"))
    float TimerTickRate = 0.3f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Radius = 20.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings", meta = (ClampMin = "0", UIMin = "0", Units = "Centimeters"))
    float Distance = 200.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TEnumAsByte<ETraceTypeQuery> TraceTypeQuery;

    UPROPERTY(EditDefaultsOnly, Category = "Settings")
    TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

    UPROPERTY()
    USceneComponent* SceneComponent;

    UPROPERTY()
    AActor* InteractingActor;

    void InteractTick();
};
