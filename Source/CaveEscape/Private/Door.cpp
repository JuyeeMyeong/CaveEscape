// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
ADoor::ADoor()
	: bShouldOpen(false),
	ClosedLocation(FVector::ZeroVector),
	OpenedLocation(FVector::ZeroVector)
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	SetRootComponent(RootScene);

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootScene);
	DoorMesh->SetCollisionProfileName(TEXT("BlockAll"));

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootScene);
	TriggerBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnTriggerEnter);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnTriggerExit);
}

void ADoor::BeginPlay()
{
	Super::BeginPlay();

	ClosedLocation = DoorMesh->GetRelativeLocation();
}

void ADoor::OnTriggerEnter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		bShouldOpen = true;
		this->OpenDoor();
	}
}

void ADoor::OnTriggerExit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && OtherActor->ActorHasTag("Player"))
	{
		bShouldOpen = false;
		this->CloseDoor();
	}
}
