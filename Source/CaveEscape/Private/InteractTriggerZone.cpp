// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractTriggerZone.h"
#include "Components/BoxComponent.h"
#include "CaveEscapeCharacter.h"

#include "Engine/Engine.h"

AInteractTriggerZone::AInteractTriggerZone()
	: TargetInteractableActor(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	// Create and set up the TriggerBox component
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	SetRootComponent(TriggerBox);
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	// Bind overlap events
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AInteractTriggerZone::OnTriggerEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &AInteractTriggerZone::OnTriggerExit);
}

void AInteractTriggerZone::BeginPlay()
{
}

void AInteractTriggerZone::OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (ACaveEscapeCharacter* Player = Cast<ACaveEscapeCharacter>(OtherActor))
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Actor's in TriggerBox"));
		}
		Player->SetCurrentTriggerZone(this);
	}
}

void AInteractTriggerZone::OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (ACaveEscapeCharacter* Player = Cast<ACaveEscapeCharacter>(OtherActor))
	{
		Player->SetCurrentTriggerZone(nullptr);
	}
}
