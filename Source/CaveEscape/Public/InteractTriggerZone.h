// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InteractTriggerZone.generated.h"

class UBoxComponent;

UCLASS()
class CAVEESCAPE_API AInteractTriggerZone : public AActor
{
	GENERATED_BODY()
	
public:	
	AInteractTriggerZone();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerBox;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Trigger", meta = (ExposeOnSpawn = true))
	AActor* TargetInteractableActor;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerEnter(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerExit(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
