// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuzzleItemBase.h"
#include "KeyItem.generated.h"

UCLASS()
class CAVEESCAPE_API AKeyItem : public APuzzleItemBase
{
	GENERATED_BODY()
	
public:
	AKeyItem();

	virtual void Interact() override;

	int32 GetKeyOrder() const { return KeyOrder; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyItem")
	int32 KeyOrder;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyItem")
	FText KeyDescription;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyItem")
	bool bIsUsable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "KeyItem")
	bool bIsCollected;
};
