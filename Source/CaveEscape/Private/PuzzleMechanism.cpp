// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleMechanism.h"
#include "PuzzleSlotBase.h"
#include "KeySlot.h"
#include "Door.h"

APuzzleMechanism::APuzzleMechanism()
{
	PrimaryActorTick.bCanEverTick = false;
}

void APuzzleMechanism::TrySolve()
{
	for (APuzzleSlotBase* Slot : PuzzleSlots)
	{
		if (AKeySlot* KeySlot = Cast<AKeySlot>(Slot))
		{
			if (!KeySlot->IsCorrectPlaced_Implementation())
			{
				return;
			}
		}
	}

	if (TargetDoor)
	{
		TargetDoor->OpenDoor();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("TargetDoor is not set!"));
	}
}



