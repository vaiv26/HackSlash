// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashCharacter.h"

#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/SlashPlayerController.h"
#include "PlayerController/SlashPlayerState.h"
#include "UI/HUD/SlashHUD.h"

ASlashCharacter::ASlashCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;
 
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

void ASlashCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Init ability actor info for Server
	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void ASlashCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	//Init ability actor info for the client
	InitAbilityActorInfo();
}

void ASlashCharacter::InitAbilityActorInfo()
{
	ASlashPlayerState* SlashPlayerState = GetPlayerState<ASlashPlayerState>();
	check(SlashPlayerState);
	SlashPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(SlashPlayerState, this);
	AbilitySystemComponent =  SlashPlayerState->GetAbilitySystemComponent();
	AttributeSet = SlashPlayerState->GetAttributeSet();
	AbilitySystemComponent->InitAbilityActorInfo(SlashPlayerState, this);

	//This is the place we place an if check and not an assert as in the client all three player controllers are not present
	if (ASlashPlayerController* SlashPlayerController =  Cast<ASlashPlayerController>(GetController()))
	{
		ASlashHUD* SlashHUD = Cast<ASlashHUD>(SlashPlayerController->GetHUD());
		if (SlashHUD)
		{
			SlashHUD->InitOverlay(SlashPlayerController, SlashPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
