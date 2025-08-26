// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/Controllers/MHMAnimalAiController.h"
#include "Navigation/PathFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Characters/Components/AI/MHMAiComponent.h"
#include "Characters/Components/AI/MHMEscapeAiComponent.h"
#include "Characters/Components/AI/MHMPatrolAiComponent.h"
#include "Characters/Interfaces/MHMPlayerInfo.h"

AMHMAnimalAiController::AMHMAnimalAiController() : Super()
{
    PatrolAiComponent = CreateDefaultSubobject<UMHMPatrolAiComponent>(TEXT("PatrolAiComponent"));
    EscapeAiComponent = CreateDefaultSubobject<UMHMEscapeAiComponent>(TEXT("EscapeAiComponent"));

    check(EscapeAiComponent);
    EscapeAiComponent->OnEscaped.AddUObject(this, &ThisClass::OnEscaped);

    UAISenseConfig_Sight* SightSense = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("SightSense"));
    check(SightSense);
    SightSense->DetectionByAffiliation.bDetectNeutrals = true;

    AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerceptionComponent"));
    check(AIPerceptionComponent);
    AIPerceptionComponent->ConfigureSense(*SightSense);
    AIPerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ThisClass::OnTargetPerceptionUpdated);
}

void AMHMAnimalAiController::OnEscaped()
{
    StartAiComponent(PatrolAiComponent);
}

void AMHMAnimalAiController::StartAiComponent(UMHMAiComponent* AiComponent)
{
    check(AiComponent);
    if (CurrentAiComponent != AiComponent)
    {
        if (CurrentAiComponent)
        {
            CurrentAiComponent->Stop();
        }
        CurrentAiComponent = AiComponent;
        CurrentAiComponent->Start(this);
    }
}

void AMHMAnimalAiController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
    if (Cast<IMHMPlayerInfo>(Actor))
    {
        check(EscapeAiComponent);
        EscapeAiComponent->SetEnemy(Actor);
        StartAiComponent(EscapeAiComponent);
    }
}

void AMHMAnimalAiController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
    Super::OnMoveCompleted(RequestID, Result);

    check(CurrentAiComponent);
    CurrentAiComponent->OnMoveCompleted(Result.IsSuccess());
}

void AMHMAnimalAiController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    check(InPawn);
    check(PatrolAiComponent);

    InPawn->OnTakePointDamage.AddDynamic(this, &ThisClass::PointDamage);

    PatrolAiComponent->SetStartLocation(InPawn->GetActorLocation());
    StartAiComponent(PatrolAiComponent);
}

void AMHMAnimalAiController::PointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy,
                                         FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName,
                                         FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{

    check(EscapeAiComponent);
    EscapeAiComponent->SetEnemy(DamageCauser);
    EscapeAiComponent->DamageHasBeenReceived();
    StartAiComponent(EscapeAiComponent);
}