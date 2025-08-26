// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MHMSpawner.generated.h"

class UBoxComponent;

UCLASS()
class MEDIEVALHUNTSMAN_API AMHMSpawner : public AActor
{
    GENERATED_BODY()

public:
    AMHMSpawner();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Settings")
    UBoxComponent* BoxComponent;

    virtual void BeginPlay() override;

private:
    UPROPERTY(EditAnywhere, Category = "Settings")
    TSubclassOf<AActor> ActorClass;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "0", UIMin = "0"))
    uint32 Count = 1;

    UPROPERTY(EditAnywhere, Category = "Settings", meta = (ClampMin = "4", UIMin = "4"))
    float TimerRate = 10.0f;

    UPROPERTY()
    TArray<AActor*> Actors;

    FTimerHandle TimerHandle;

    void Spawn();
    FVector GetSpawnLocation() const;
    void CheckActors();
};
