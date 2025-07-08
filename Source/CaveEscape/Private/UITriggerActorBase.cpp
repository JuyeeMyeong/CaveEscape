// Fill out your copyright notice in the Description page of Project Settings.

#include "UITriggerActorBase.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AUITriggerActorBase::AUITriggerActorBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

bool AUITriggerActorBase::HandleTriggerReact_Implementation()
{
	DisplayUI();
	return true;
}

void AUITriggerActorBase::DisplayUI()
{

	if (UIWidgetClass && !ActiveWidget)
	{

		APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
		if (PC)
		{
			ActiveWidget = CreateWidget<UUserWidget>(PC, UIWidgetClass);
			if (ActiveWidget)
			{
				ActiveWidget->AddToViewport();
				SetupInputBlock();
			}
		}
	}
}

void AUITriggerActorBase::HideUI()
{
	if (ActiveWidget)
	{
		ActiveWidget->RemoveFromParent();
		ActiveWidget = nullptr;
		ReleaseInputBlock();
	}
}

bool AUITriggerActorBase::HasOpenWidget() const
{
	return ActiveWidget != nullptr;
}

void AUITriggerActorBase::SetupInputBlock()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);

		if (ActiveWidget)
		{
			InputMode.SetWidgetToFocus(ActiveWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
	}
}

void AUITriggerActorBase::ReleaseInputBlock()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (PC)
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
}


