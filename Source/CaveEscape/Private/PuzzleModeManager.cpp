// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzleModeManager.h"
#include "PuzzleSlotBase.h"
#include "PuzzleItemBase.h"
#include "InventoryComponent.h"
#include "CaveEscapeCharacter.h"
#include "Kismet/GameplayStatics.h"

#include "Engine/Engine.h"

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
	// 함수 진입 확인
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, FString::Printf(TEXT("HandleKeyInput() Called with CommandNum: %d"), commandNum));
	}

	if (!bInPuzzleMode || !OwningCharacter)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("PuzzleMode is off or OwningCharacter is null"));
		}
		return;
	}

	int32 TargetSlotIndex = commandNum;

	TArray<AActor*> FoundSlots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APuzzleSlotBase::StaticClass(), FoundSlots);

	for (AActor* Actor : FoundSlots)
	{
		if (APuzzleSlotBase* SlotBase = Cast<APuzzleSlotBase>(Actor))
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Cyan, FString::Printf(TEXT("Found Slot: %s | SlotIndex: %d"), *SlotBase->GetName(), SlotBase->SlotIndex));
			}

			if (SlotBase->SlotIndex == TargetSlotIndex)
			{
				if (GEngine)
				{
					GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, TEXT("Matching Slot Found!"));
				}

				UInventoryComponent* Inventory = OwningCharacter->FindComponentByClass<UInventoryComponent>();
				if (!Inventory)
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Inventory Component Not Found!"));
					}
					return;
				}

				APuzzleItemBase* SelectedItem = Inventory->GetSelectedItem();
				if (SelectedItem)
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Yellow, FString::Printf(TEXT("SelectedItem: %s will be placed."), *SelectedItem->GetName()));
					}
					SlotBase->PlaceItem(SelectedItem);
				}
				else
				{
					if (GEngine)
					{
						GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("No item selected in inventory."));
					}
				}
				break;
			}
		}
	}
}

