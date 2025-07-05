// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractTriggerZone.h"
#include "Components/BoxComponent.h"

AInteractTriggerZone::AInteractTriggerZone()
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