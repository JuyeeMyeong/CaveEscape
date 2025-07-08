// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleModeManager.h"
#include "PuzzleSlotBase.h"
#include "PuzzleItemBase.h"
#include "InventoryComponent.h"
#include "CaveEscapeCharacter.h"
#include "Kismet/GameplayStatics.h"

UPuzzleModeManager::UPuzzleModeManager()
	: bInPuzzleMode(false),
	OwningCharacter(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPuzzleModeManager::EnterPuzzleMode()
{
	OwningCharacter = Cast<ACaveEscapeCharacter>(GetOwner());

	if (OwningCharacter)
	{
		bInPuzzleMode = true;
		OwningCharacter->SetPuzzleInputMode(true);
	}

}

void UPuzzleModeManager::ExitPuzzleMode()
{
	if (OwningCharacter)
	{
		OwningCharacter->SetPuzzleInputMode(false);
	}

	bInPuzzleMode = false;
	OwningCharacter = nullptr;
}

void UPuzzleModeManager::HandleKeyInput(int32 commandNum)
{

	if (!bInPuzzleMode || !OwningCharacter)
	{
		return;
	}

	int32 TargetSlotIndex = commandNum;

	TArray<AActor*> FoundSlots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleSlotBase::StaticClass(), FoundSlots);

	for (AActor* Actor : FoundSlots)
	{
		if (APuzzleSlotBase* SlotBase = Cast<APuzzleSlotBase>(Actor))
		{

			if (SlotBase->SlotIndex == TargetSlotIndex)
			{

				UInventoryComponent* Inventory = OwningCharacter->FindComponentByClass<UInventoryComponent>();
				if (!Inventory)
				{
					return;
				}

				APuzzleItemBase* SelectedItem = Inventory->GetSelectedItem();
				if (SelectedItem)
				{
					SlotBase->PlaceItem(SelectedItem);
				}
				break;
			}
		}
	}
}

