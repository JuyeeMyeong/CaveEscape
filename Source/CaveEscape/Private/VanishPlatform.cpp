// Fill out your copyright notice in the Description page of Project Settings.


#include "VanishPlatform.h"
#include "Components/BoxComponent.h"
#include "PlatformDataRow.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
AVanishPlatform::AVanishPlatform()
	: StartDelay(0.0f)
{
	PrimaryActorTick.bCanEverTick = false;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AVanishPlatform::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AVanishPlatform::OnOverlapEnd);
}

void AVanishPlatform::InitializeFromData(const FPlatformDataRow& Data)
{
	Super::InitializeFromData(Data);
	StartDelay = Data.StartDelay;
}

void AVanishPlatform::VanishPlatform()
{
	if (PlatformMesh)
	{
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		PlatformMesh->SetVisibility(false);
		SetActorHiddenInGame(true);
	}
}

void AVanishPlatform::ResetPlatform()
{
	if (TriggerBox)
	{
		TriggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		if (PlatformMesh)
		{
			PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			PlatformMesh->SetVisibility(true);
			SetActorHiddenInGame(false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("PlatformMesh is null in ResetPlatform."));
		}
	}
}

void AVanishPlatform::ResetTimer()
{
	GetWorldTimerManager().SetTimer(
		DelayHandle,
		this,
		&AVanishPlatform::DoNothing,
		0.1f,
		false
	);
}

void AVanishPlatform::DoNothing()
{
}

void AVanishPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		ResetTimer();
		if (StartDelay == 0.0f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid StartDelay. It should be > 0.0f"));
		}

		GetWorldTimerManager().SetTimer(
			DelayHandle, 
			this, 
			&AVanishPlatform::VanishPlatform, 
			StartDelay, 
			false
		);
	}

}

void AVanishPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		GetWorldTimerManager().SetTimer(
			DelayHandle, 
			this, 
			&AVanishPlatform::ResetPlatform, 
			StartDelay, 
			false
		);
	}
}

