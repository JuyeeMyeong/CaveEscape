// Fill out your copyright notice in the Description page of Project Settings.


#include "KeySlot.h"
#include "KeyItem.h"

bool AKeySlot::PlaceItem(APuzzleItemBase* Item)
{
	Super::PlaceItem(Item);

	return false;
}

bool AKeySlot::IsCorrectPlaced_Implementation() const
{
	if (const AKeyItem* Keyitem = Cast<AKeyItem>(PlacedItem))
	{
		if (Keyitem->GetKeyOrder() == SlotIndex + 1)
		{
			return true;
		}
	}

	return false;
}