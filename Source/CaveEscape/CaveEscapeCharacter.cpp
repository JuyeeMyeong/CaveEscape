// Copyright Epic Games, Inc. All Rights Reserved.

#include "CaveEscapeCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InteractTriggerZone.h"
#include "UITriggerActorBase.h"
#include "PuzzleModeManager.h"
#include "EngineUtils.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"


#include "Engine/Engine.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

ACaveEscapeCharacter::ACaveEscapeCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	bIsInPuzzleMode = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	PuzzleModeManager = CreateDefaultSubobject<UPuzzleModeManager>(TEXT("PuzzleModeManager"));

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)
}

void ACaveEscapeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACaveEscapeCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ACaveEscapeCharacter::Look);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACaveEscapeCharacter::Look);

		// Interaction
		EnhancedInputComponent->BindAction(CloseUIAction, ETriggerEvent::Triggered, this, &ACaveEscapeCharacter::CloseUI);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACaveEscapeCharacter::TryInteract);

		// PuzzleSlots
		EnhancedInputComponent->BindAction(PlaceItem1Action, ETriggerEvent::Started, this, &ACaveEscapeCharacter::HandlePlaceItemKey1);
		EnhancedInputComponent->BindAction(PlaceItem2Action, ETriggerEvent::Started, this, &ACaveEscapeCharacter::HandlePlaceItemKey2);
		EnhancedInputComponent->BindAction(PlaceItem3Action, ETriggerEvent::Started, this, &ACaveEscapeCharacter::HandlePlaceItemKey3);
		EnhancedInputComponent->BindAction(PlaceItem4Action, ETriggerEvent::Started, this, &ACaveEscapeCharacter::HandlePlaceItemKey4);

	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACaveEscapeCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	// route the input
	DoMove(MovementVector.X, MovementVector.Y);
}

void ACaveEscapeCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	// route the input
	DoLook(LookAxisVector.X, LookAxisVector.Y);
}

void ACaveEscapeCharacter::DoMove(float Right, float Forward)
{
	if (GetController() != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = GetController()->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, Forward);
		AddMovementInput(RightDirection, Right);
	}
}

void ACaveEscapeCharacter::DoLook(float Yaw, float Pitch)
{
	if (GetController() != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(Yaw);
		AddControllerPitchInput(Pitch);
	}
}

void ACaveEscapeCharacter::DoJumpStart()
{
	// signal the character to jump
	Jump();
}

void ACaveEscapeCharacter::DoJumpEnd()
{
	// signal the character to stop jumping
	StopJumping();
}

void ACaveEscapeCharacter::CloseUI()
{

	for (TActorIterator<AUITriggerActorBase> It(GetWorld()); It; ++It)
	{
		AUITriggerActorBase* UIActor = *It;
		if (UIActor && UIActor->HasOpenWidget())
		{
			UIActor->HideUI();
			break;
		}
	}
}

void ACaveEscapeCharacter::TryInteract()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("TryInteract() being called"));
	}

	if (CurrentTriggerZone)
	{
		AActor* Target = CurrentTriggerZone->TargetInteractableActor;

		if (!Target)
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, TEXT("Target x -> puzzlemode"));
			}

			if (UPuzzleModeManager* PuzzleManager = FindComponentByClass<UPuzzleModeManager>())
			{
				PuzzleManager->EnterPuzzleMode();
				bIsInPuzzleMode = true;

			}
			return;
		}

		if (Target->Implements<UReactToTraggerInterface>())
		{
			IReactToTraggerInterface::Execute_HandleTriggerReact(Target);
		}
	}
}

void ACaveEscapeCharacter::HandlePlaceItemKey1()
{
	if (GEngine)
	{
		const FString DebugMessage = FString::Printf(TEXT("PuzzleMode: %s"),
			PuzzleModeManager && PuzzleModeManager->IsInPuzzleMode() ? TEXT("TRUE") : TEXT("FALSE"));

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Cyan, DebugMessage);
	}

	if (PuzzleModeManager && PuzzleModeManager->IsInPuzzleMode())
	{
		PuzzleModeManager->HandleKeyInput(0); // 0¹ø ½½·Ô
	}
}

void ACaveEscapeCharacter::HandlePlaceItemKey2()
{
	if (PuzzleModeManager && PuzzleModeManager->IsInPuzzleMode())
	{
		PuzzleModeManager->HandleKeyInput(1);
	}
}

void ACaveEscapeCharacter::HandlePlaceItemKey3()
{
	if (PuzzleModeManager && PuzzleModeManager->IsInPuzzleMode())
	{
		PuzzleModeManager->HandleKeyInput(2);
	}
}

void ACaveEscapeCharacter::HandlePlaceItemKey4()
{
	if (PuzzleModeManager && PuzzleModeManager->IsInPuzzleMode())
	{
		PuzzleModeManager->HandleKeyInput(3);
	}
}

void ACaveEscapeCharacter::SetCurrentTriggerZone(AInteractTriggerZone* Zone)
{
	CurrentTriggerZone = Zone;
}

void ACaveEscapeCharacter::SetPuzzleInputMode(bool bEnable, UUserWidget* OptionalWidget)
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC) return;

	if (bEnable)
	{
		PC->SetShowMouseCursor(true);

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);

		if (OptionalWidget)
		{
			InputMode.SetWidgetToFocus(OptionalWidget->TakeWidget());
		}

		PC->SetInputMode(InputMode);
	}
	else
	{
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
}
