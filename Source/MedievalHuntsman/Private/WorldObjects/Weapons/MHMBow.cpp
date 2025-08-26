// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/Weapons/MHMBow.h"
#include "Components/AudioComponent.h"
#include "Components/TimelineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"
#include "WorldObjects/interactableObjects/Items/MHMArrow.h"

AMHMBow::AMHMBow() : Super()
{
    ChargeAudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ChargeAudioComponent"));
    check(ChargeAudioComponent);
    ChargeAudioComponent->SetupAttachment(GetRootComponent());
    ChargeAudioComponent->SetAutoActivate(false);
}

void AMHMBow::StartCharge()
{
    check(GetWorld());
    check(OwnerInventory);
    check(ChargeTimeLine);
    check(ChargeAudioComponent);

    if (OwnerInventory->HasItem(ArrowRowName))
    {
        Arrow = GetWorld()->SpawnActor<AMHMArrow>(ArrowClass, FVector::ZeroVector, FRotator::ZeroRotator);
        check(Arrow);
        Arrow->SetOwner(GetOwner());
        Arrow->AttachToComponent(SkeletalMeshComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale,
                                 ArrowSocketName);
        ChargeTimeLine->PlayFromStart();
        ChargeAudioComponent->Play();
    }
}

void AMHMBow::StopCharge()
{
    check(ChargeTimeLine);
    check(ChargeAudioComponent);

    if (IsValid(Arrow))
    {
        Arrow->Destroy();
    }
    ChargeTimeLine->Stop();
    ChargeAudioComponent->Stop();
    Charge = 0.0f;
}

void AMHMBow::Fire()
{
    if (!IsValid(Arrow)) return;

    check(OwnerInventory);

    Arrow->SetDamageAmount(FMHMItemHelper::GetDamage(GetRowName()));
    Arrow->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    Arrow->Fire(Charge);
    Arrow = nullptr;

    StopCharge();
    UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    if (OwnerInventory->RemoveItem(ArrowRowName)) return;

    checkNoEntry();
}

float AMHMBow::GetCharge() const
{
    return Charge;
}

void AMHMBow::BeginPlay()
{
    Super::BeginPlay();
    ChargeTimeLine = NewObject<UTimelineComponent>(this);
    check(ChargeTimeLine);
    ChargeTimeLine->SetLooping(false);

    FOnTimelineFloat ProgressChargeFunction;
    ProgressChargeFunction.BindUFunction(this, FName(TEXT("ProgressCharge")));

    ChargeTimeLine->AddInterpFloat(ChargeCurve, ProgressChargeFunction);
    ChargeTimeLine->RegisterComponent();

    OwnerInventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(GetOwner());
}

void AMHMBow::ProgressCharge(const float value)
{
    Charge = value;
}
