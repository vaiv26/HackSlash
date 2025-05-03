// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SlashPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/InputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "Input/SlashInputComponent.h"

ASlashPlayerController::ASlashPlayerController()
{
	bReplicates = true;
}

void ASlashPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(SlashContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(SlashContext,0);
	}
	
	// Set input mode to game only and consume mouse clicks
	FInputModeGameOnly InputModeGameOnly;
	InputModeGameOnly.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputModeGameOnly);
    
	// Hide the mouse cursor
	bShowMouseCursor = false;
}

void ASlashPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	USlashInputComponent* SlashInputComponent = CastChecked<USlashInputComponent>(InputComponent);
	SlashInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASlashPlayerController::Move);
	SlashInputComponent->BindAction(LookAround, ETriggerEvent::Triggered, this, &ASlashPlayerController::Look);
	SlashInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void ASlashPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ASlashPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	AddYawInput(InputAxisVector.X);
	AddPitchInput(InputAxisVector.Y);
}

void ASlashPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
}

void ASlashPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void ASlashPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

USlashAbilitySystemComponent* ASlashPlayerController::GetASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<USlashAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
