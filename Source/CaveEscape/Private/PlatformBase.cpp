// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformBase.h"
#include "PlatformDataRow.h"

// Sets default values
APlatformBase::APlatformBase()
	: SpawnMin(FVector::ZeroVector), 
	  SpawnMax(FVector::ZeroVector),
	  StartLocation(FVector::ZeroVector)
{
	PrimaryActorTick.bCanEverTick = false;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);
}

void APlatformBase::InitializeFromData(const FPlatformDataRow& Data)
{
	SpawnMin = Data.SpawnMin;
	SpawnMax = Data.SpawnMax;
	FVector SpawnLocation = FMath::RandPointInBox(FBox(SpawnMin, SpawnMax));
	SetActorLocation(SpawnLocation);

	StartLocation = SpawnLocation;
}

