// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Door.h"
#include "ExitSliding.generated.h"


UCLASS()
class CAVEESCAPE_API AExitSliding : public ADoor
{
	GENERATED_BODY()
	
public:
	AExitSliding();

	virtual void Tick(float DeltaTime) override;

	virtual void OpenDoor() override;
	virtual void CloseDoor() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ExitSliding")
	float SlideSpeed;

private:
	virtual void BeginPlay() override;

	bool bIsMoving;
};
