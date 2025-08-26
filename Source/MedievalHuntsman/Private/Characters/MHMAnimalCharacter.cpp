// Copyright Epic Games, Inc. All Rights Reserved.

#include "Characters/MHMAnimalCharacter.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/Components/MHMHealthComponent.h"
#include "Core/Components/MHMInteractWidgetComponent.h"
#include "Core/Components/MHMInventoryComponent.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Interfaces/MHMInventory.h"
#include "Core/Interfaces/MHMRowName.h"

AMHMAnimalCharacter::AMHMAnimalCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    bUseControllerRotationYaw = false;

    check(GetCharacterMovement());
    GetCharacterMovement()->bOrientRotationToMovement = true;

    BlockCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BlockCollision"));
    check(BlockCollision);
    BlockCollision->SetupAttachment(GetRootComponent());

    InteractWidgetComponent = CreateDefaultSubobject<UMHMInteractWidgetComponent>(TEXT("InteractWidgetComponent"));
    check(InteractWidgetComponent);
    InteractWidgetComponent->SetupAttachment(GetMesh());

    AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
    check(AudioComponent);
    AudioComponent->SetupAttachment(GetRootComponent());
}

void AMHMAnimalCharacter::Interact(AActor* OtherActor)
{
    check(HealthComponent);
    if (HealthComponent->IsDead())
    {
        IMHMInventory* OtherInventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(OtherActor);
        OtherInventory->TransferFromInventory(InventoryComponent);

        const TArray<AActor*>& Arrows = GetAddedArrows();
        for (AActor* Actor : Arrows)
        {
            if (!IsValid(Actor)) continue;
            if (const IMHMRowName* ItemRowName = Cast<IMHMRowName>(Actor))
            {
                OtherInventory->AddItem(ItemRowName->GetRowName());
                Actor->Destroy();
            }
        }
        Destroy();
    }
}

void AMHMAnimalCharacter::OnEnter()
{
    check(HealthComponent);
    if (HealthComponent->IsDead())
    {
        check(InteractWidgetComponent);
        InteractWidgetComponent->SetVisibility(true);
    }
}

void AMHMAnimalCharacter::OnLeave()
{
    check(InteractWidgetComponent);
    InteractWidgetComponent->SetVisibility(false);
}

void AMHMAnimalCharacter::Dead()
{
    Super::Dead();

    check(BlockCollision);
    check(GetController());

    BlockCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    GetController()->Destroy();
}
