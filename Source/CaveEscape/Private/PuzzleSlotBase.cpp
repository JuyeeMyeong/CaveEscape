// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleSlotBase.h"
#include "PuzzleItemBase.h"
#include "Components/StaticMeshComponent.h"
#include "PuzzleMechanism.h"
#include "CaveEscapeCharacter.h"
#include "PuzzleModeManager.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"	

APuzzleSlotBase::APuzzleSlotBase()
	: PlacedItem(nullptr),
	SlotIndex(0),
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

	if (PuzzleMechanism)
	{
		PuzzleMechanism->TrySolve();
	}

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


bool APuzzleSlotBase::HandleTriggerReact_Implementation()
{
	if (ACaveEscapeCharacter* PlayerCharacter = Cast<ACaveEscapeCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0)))
	{
		if (UPuzzleModeManager* PuzzleManager = PlayerCharacter->FindComponentByClass<UPuzzleModeManager>())
		{
			PuzzleManager->EnterPuzzleMode();
			return true;
		}
	}
	return false;
}
