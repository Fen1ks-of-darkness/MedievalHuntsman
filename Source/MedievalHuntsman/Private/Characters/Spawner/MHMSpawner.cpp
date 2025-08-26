// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Spawner/MHMSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

AMHMSpawner::AMHMSpawner()
{
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    check(BoxComponent);
    SetRootComponent(BoxComponent);
    BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AMHMSpawner::BeginPlay()
{
    Super::BeginPlay();
    for (uint32 i = 0; i < Count; ++i)
    {
        Spawn();
    }
    GetWorldTimerManager().SetTimer(TimerHandle, this, &ThisClass::CheckActors, TimerRate, true);
}

void AMHMSpawner::Spawn()
{
    check(GetWorld());
    AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorClass, GetSpawnLocation(), FRotator::ZeroRotator);
    if (Actor)
    {
        Actors.Add(Actor);
    }
    else
    {
        Spawn();
    }
}

FVector AMHMSpawner::GetSpawnLocation() const
{
    check(BoxComponent);
    const FTransform BoxComponentTransform = {BoxComponent->GetComponentRotation(),
                                              BoxComponent->GetComponentLocation(), FVector::OneVector};

    const FVector RandomPoint =
        UKismetMathLibrary::RandomPointInBoundingBox(FVector::ZeroVector, BoxComponent->GetScaledBoxExtent());
    return UKismetMathLibrary::TransformLocation(BoxComponentTransform, RandomPoint);
}

void AMHMSpawner::CheckActors()
{
    const uint32 CountActors = Actors.Num();
    for (uint32 i = 0; i < CountActors; ++i)
    {
        if (!IsValid(Actors[i]))
        {
            Actors.RemoveAt(i);
            Spawn();
        }
    }
}
