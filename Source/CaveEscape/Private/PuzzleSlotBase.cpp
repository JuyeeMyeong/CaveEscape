// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSlotBase.h"
#include "PuzzleItemBase.h"
#include "Components/StaticMeshComponent.h"

APuzzleSlotBase::APuzzleSlotBase()
	: PlacedItem(nullptr),
	PlacedLocation(FVector::ZeroVector)
{
	PrimaryActorTick.bCanEverTick = false;

	SlotMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SlotMesh"));
	SetRootComponent(SlotMesh);
	SlotMesh->SetCollisionProfileName(TEXT("BlockAll"));
}

bool APuzzleSlotBase::PlaceItem(APuzzleItemBase* Item)
{
	if (!Item) return false;

	PlacedItem = Item;
	
	PlacedItem->AttachToComponent(SlotMesh, FAttachmentTransformRules::KeepRelativeTransform);
	PlacedItem->SetActorRelativeLocation(PlacedLocation);
	return true;
}

void APuzzleSlotBase::RemoveItem()
{
	if (PlacedItem)
	{
		PlacedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		PlacedItem = nullptr;
	}
}

bool APuzzleSlotBase::IsCorrectPlaced_Implementation() const
{
	return false;
}


