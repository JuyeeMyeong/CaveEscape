// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "RotatePlatform.generated.h"

struct FPlatformDataRow;

UCLASS()
class CAVEESCAPE_API ARotatePlatform : public APlatformBase
{
	GENERATED_BODY()
	
public:
	ARotatePlatform();

	virtual void Tick(float DeltaTime) override;

	virtual void InitializeFromData(const FPlatformDataRow& Data) override;

private:
	FRotator RotationRate;
};
