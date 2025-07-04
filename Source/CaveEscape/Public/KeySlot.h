// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleSlotBase.h"
#include "KeySlot.generated.h"

class APuzzleItemBase;

UCLASS()
class CAVEESCAPE_API AKeySlot : public APuzzleSlotBase
{
	GENERATED_BODY()

public:
	
	virtual bool PlaceItem(APuzzleItemBase* Item) override;

	virtual bool IsCorrectPlaced_Implementation() const override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 SlotIndex;
};
