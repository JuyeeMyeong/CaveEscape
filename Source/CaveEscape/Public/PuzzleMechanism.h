// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleMechanism.generated.h"

class APuzzleSLotBase;
class ADoor;

UCLASS()
class CAVEESCAPE_API APuzzleMechanism : public AActor
{
	GENERATED_BODY()
	
public:	
	APuzzleMechanism();

	UFUNCTION(BlueprintCallable, Category = "Puzzle")
	void TrySolve();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<class APuzzleSlotBase*> PuzzleSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	ADoor* TargetDoor;
};
