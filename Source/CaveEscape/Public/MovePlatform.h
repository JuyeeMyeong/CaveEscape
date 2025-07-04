// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "MovePlatform.generated.h"

struct FPlatformDataRow;

UCLASS()
class CAVEESCAPE_API AMovePlatform : public APlatformBase
{
	GENERATED_BODY()

public:
	AMovePlatform();

	virtual void Tick(float DeltaTime) override;

	virtual void InitializeFromData(const FPlatformDataRow& Data) override;

private:
	FVector Range;
	FVector MaxRange;
	float MoveSpeed;
	bool bLooping;
	bool bIsMovingBack;
};
