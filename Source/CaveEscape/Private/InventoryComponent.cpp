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

void UInventoryComponent::SelectNextItem()
{
	if (Items.Num() == 0) return;

	SelectedIndex = (SelectedIndex + 1) % Items.Num();
}

void UInventoryComponent::SelectPreviousItem()
{
	if (Items.Num() == 0) return;

	SelectedIndex = (SelectedIndex - 1 + Items.Num()) % Items.Num();
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

