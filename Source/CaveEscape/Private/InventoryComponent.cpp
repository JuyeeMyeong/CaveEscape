// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "PuzzleItemBase.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SelectedIndex = 0;
}

bool UInventoryComponent::AddItem(APuzzleItemBase* Item)
{
	if (Item && Items.Num() < 10)
	{
		Items.Add(Item);
		return true;
	}
	return false;
}

void UInventoryComponent::SelectItemByIndex(int32 Index)
{
	if (Items.IsValidIndex(Index))
	{
		SelectedIndex = Index;
	}
}

APuzzleItemBase* UInventoryComponent::GetSelectedItem() const
{
	if (Items.IsValidIndex(SelectedIndex))
	{
		return Items[SelectedIndex];
	}
	return nullptr;
}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	for (TSubclassOf<APuzzleItemBase> ItemClass : DefaultItemClasses)
	{
		if (ItemClass)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetOwner();

			APuzzleItemBase* NewItem = GetWorld()->SpawnActor<APuzzleItemBase>(
				ItemClass,
				FVector::ZeroVector,
				FRotator::ZeroRotator,
				SpawnParams
			);

			if (NewItem)
			{
				AddItem(NewItem);
			}
		}
	}
}

