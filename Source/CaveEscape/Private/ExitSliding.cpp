// Fill out your copyright notice in the Description page of Project Settings.


#include "ExitSliding.h"

AExitSliding::AExitSliding()
	: SlideSpeed(200.0f),
	bIsMoving(false)
{
	PrimaryActorTick.bCanEverTick = true;
}

void AExitSliding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bIsMoving || !DoorMesh)
	{
		return;
	}

	FVector CurrentLocation = DoorMesh->GetRelativeLocation();
	FVector TargetLocation = bShouldOpen ? OpenedLocation : ClosedLocation;
	FVector NewLocation = FMath::VInterpTo(CurrentLocation, TargetLocation, DeltaTime, SlideSpeed);

	DoorMesh->SetRelativeLocation(NewLocation);
	
	if (FVector::Dist(NewLocation, TargetLocation) < KINDA_SMALL_NUMBER)
	{
		bIsMoving = false;
		if (bShouldOpen)
		{
			DoorMesh->SetRelativeLocation(OpenedLocation);
		}
		else
		{
			DoorMesh->SetRelativeLocation(ClosedLocation);
		}
	}
}

void AExitSliding::OpenDoor()
{
	if (DoorMesh)
	{
		bIsMoving = true;
		
	}
}

void AExitSliding::CloseDoor()
{
	if (DoorMesh)
	{
		bIsMoving = true;
	}
}

void AExitSliding::BeginPlay()
{
	Super::BeginPlay();

	if (DoorMesh)
	{
		OpenedLocation = ClosedLocation + FVector(-200.0f, 0.0f, 0.0f);
	}
}
