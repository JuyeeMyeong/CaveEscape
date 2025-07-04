// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleSlotBase.generated.h"

class UStaticMeshComponent;
class APuzzleItemBase;

UCLASS()
class CAVEESCAPE_API APuzzleSlotBase : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleSlotBase();

	virtual bool PlaceItem(APuzzleItemBase* Item);
	void RemoveItem();

	virtual bool IsCorrectPlaced_Implementation() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	UStaticMeshComponent* SlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APuzzleItemBase* PlacedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FVector PlacedLocation; // BP에서 수정
};
