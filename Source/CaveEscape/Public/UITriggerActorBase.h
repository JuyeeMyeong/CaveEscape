// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReactToTraggerInterface.h"
#include "UITriggerActorBase.generated.h"

UCLASS(Abstract)
class CAVEESCAPE_API AUITriggerActorBase : public AActor, public IReactToTraggerInterface
{
	GENERATED_BODY()

public:
	AUITriggerActorBase();

	virtual bool HandleTriggerReact_Implementation() override;

	virtual void DisplayUI();
	virtual void HideUI();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool HasOpenWidget() const;

protected:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<UUserWidget> UIWidgetClass;

	UPROPERTY()
	UUserWidget* ActiveWidget;

	void SetupInputBlock();
	void ReleaseInputBlock();
};

