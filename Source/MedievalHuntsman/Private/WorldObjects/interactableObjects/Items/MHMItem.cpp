// Copyright Epic Games, Inc. All Rights Reserved.

#include "WorldObjects/interactableObjects/Items/MHMItem.h"
#include "Core/Helpers/MHMHelperFunctions.h"
#include "Core/Helpers/MHMItemHelper.h"
#include "Core/Interfaces/MHMInventory.h"

void AMHMItem::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    ItemRow.DataTable = FMHMItemHelper::GetDataTable();

    InitMesh();
}

void AMHMItem::InitMesh()
{
    if (!ItemRow.RowName.IsNone())
    {
        check(StaticMeshComponent);
        StaticMeshComponent->SetStaticMesh(FMHMItemHelper::GetStaticMesh(ItemRow.RowName));
    }
}

void AMHMItem::SetRowName(const FName& InRowName)
{
    ItemRow.RowName = InRowName;
    InitMesh();
}

FName AMHMItem::GetRowName() const
{
    return ItemRow.RowName;
}

FText AMHMItem::GetObjectName() const
{
    return FMHMItemHelper::GetName(ItemRow.RowName);
}

void AMHMItem::DoInteract(AActor* OtherActor)
{
    Super::DoInteract(OtherActor);
    IMHMInventory* Inventory = FMHMHelperFunctions::GetComponentByInterface<IMHMInventory>(OtherActor);
    if (Inventory)
    {
        Inventory->AddItem(ItemRow.RowName);
        Destroy();
    }
}
