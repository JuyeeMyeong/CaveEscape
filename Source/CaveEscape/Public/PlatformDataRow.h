// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "PlatformDataRow.generated.h"

USTRUCT(BlueprintType)
struct FPlatformDataRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName PlatformID;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<AActor> PlatformClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float PlatformSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector PlatformRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FRotator RotationRate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float StartDelay;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bLooping;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnMin;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FVector SpawnMax;
};