// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatePlatform.h"
#include "PlatformDataRow.h"

ARotatePlatform::ARotatePlatform()
	: RotationRate(FRotator::ZeroRotator)
{
	PrimaryActorTick.bCanEverTick = true;

}

void ARotatePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (RotationRate.IsNearlyZero())
	{
		return;
	}

	FRotator DeltaRotation = RotationRate * DeltaTime;
	AddActorLocalRotation(DeltaRotation);
}

void ARotatePlatform::InitializeFromData(const FPlatformDataRow& Data)
{
	Super::InitializeFromData(Data);
	RotationRate = Data.RotationRate;
}
