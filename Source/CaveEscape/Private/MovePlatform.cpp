// Fill out your copyright notice in the Description page of Project Settings.


#include "MovePlatform.h"
#include "PlatformDataRow.h"

AMovePlatform::AMovePlatform()
	: Range(FVector::ZeroVector),
	MaxRange(FVector::ZeroVector),
	MoveSpeed(0.0f),
	bLooping(false),
	bIsMovingBack(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMovePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bLooping) return; // ø§∑π∫£¿Ã≈Õ «√∑ß∆˚¿œ ∂ß 

	const FVector CurrentLocation = GetActorLocation();

	FVector Target = bIsMovingBack ? StartLocation : MaxRange;
	FVector Direction = (Target - CurrentLocation).GetSafeNormal();
	FVector NextLocation = CurrentLocation + Direction * MoveSpeed * DeltaTime;

	if (FVector::DotProduct(Direction, (Target - NextLocation)) <= 0)
	{
		SetActorLocation(Target);
		bIsMovingBack = !bIsMovingBack;
	}
	else
	{
		SetActorLocation(NextLocation);
	}
}

void AMovePlatform::InitializeFromData(const FPlatformDataRow& Data)
{
	Super::InitializeFromData(Data);

	MoveSpeed = Data.PlatformSpeed;
	Range = Data.PlatformRange;
	bLooping = Data.bLooping;

	MaxRange = StartLocation + Range;
}