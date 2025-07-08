// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReactToTraggerInterface.h"
#include "PuzzleSlotBase.generated.h"

class UStaticMeshComponent;
class APuzzleItemBase;
class APuzzleMechanism;

UCLASS()
class CAVEESCAPE_API APuzzleSlotBase : public AActor, public IReactToTraggerInterface
{
	GENERATED_BODY()
	
public:	
	APuzzleSlotBase();

	virtual bool PlaceItem(APuzzleItemBase* Item);
	void RemoveItem();

	virtual bool IsCorrectPlaced_Implementation() const;

	virtual bool HandleTriggerReact_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	int32 SlotIndex;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	UStaticMeshComponent* SlotMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	APuzzleItemBase* PlacedItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	FVector PlacedLocation; // BP에서 수정

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Puzzle")
	APuzzleMechanism* PuzzleMechanism;

};
