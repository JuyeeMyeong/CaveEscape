// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PuzzleModeManager.generated.h"

class APuzzleSlotBase;
class ACaveEscapeCharacter;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class CAVEESCAPE_API UPuzzleModeManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPuzzleModeManager();

	void EnterPuzzleMode();
	void ExitPuzzleMode();

	void HandleKeyInput(int32 commandNum);

	UFUNCTION(BlueprintCallable)
	bool IsInPuzzleMode() const { return bInPuzzleMode; }

private:
	UPROPERTY()
	bool bInPuzzleMode;

	UPROPERTY()
	class ACaveEscapeCharacter* OwningCharacter;
};

