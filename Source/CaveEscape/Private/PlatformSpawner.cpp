// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformSpawner.h"
#include "PlatformDataRow.h"
#include "PlatformBase.h"
#include "Engine/DataTable.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
APlatformSpawner::APlatformSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlatformSpawner::BeginPlay()
{
	Super::BeginPlay();
	SpawnAllPlatforms();
}

void APlatformSpawner::SpawnAllPlatforms()
{
	if (!PlatformDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlatformDataTable is not set!"));
		return;
	}

	TArray<FPlatformDataRow*> AllRows;
	static const FString ContextString(TEXT("Platform Data Context"));
	PlatformDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty()) return;

	for (const FPlatformDataRow* DataRow : AllRows)
	{
		if (DataRow && DataRow->PlatformClass)
		{
			FActorSpawnParameters SpawnParams;
			
			APlatformBase* SpawnedPlatform = Cast<APlatformBase>(GetWorld()->SpawnActor<AActor>(DataRow->PlatformClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams));

			if (SpawnedPlatform)
			{
				SpawnedPlatform->InitializeFromData(*DataRow);
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid platform class for row"));
		}
	}

}
