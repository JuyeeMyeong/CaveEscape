// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuzzleItemBase.generated.h"

class UStaticMesh;

UCLASS(Abstract)
class CAVEESCAPE_API APuzzleItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APuzzleItemBase();

	virtual void Interact() PURE_VIRTUAL(APuzzleItemBase::Interact, );

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PuzzleItem")
	UStaticMeshComponent* ItemMesh;
};
