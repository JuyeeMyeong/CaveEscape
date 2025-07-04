// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatformBase.h"
#include "VanishPlatform.generated.h"

struct FPlatformDataRow;
class UBoxComponent;

UCLASS()
class CAVEESCAPE_API AVanishPlatform : public APlatformBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVanishPlatform();

	virtual void InitializeFromData(const FPlatformDataRow& Data) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	UBoxComponent* TriggerBox;

private: 
	float StartDelay;
	FTimerHandle DelayHandle;

	void VanishPlatform();
	void ResetPlatform();
	void ResetTimer();
	void DoNothing();

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
