// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformBase.generated.h"

class UStaticMeshComponent;
struct FPlatformDataRow;

UCLASS(Abstract)
class CAVEESCAPE_API APlatformBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlatformBase();

	// ��� �� FPlatformDataRow���� ���� Ȯ�� �ʿ�
	virtual void InitializeFromData(const FPlatformDataRow& Data);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	FVector SpawnMin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform")
	FVector SpawnMax;

	FVector StartLocation;
};
