// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashCharacter.h"

#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PlayerController/SlashPlayerState.h"

ASlashCharacter::ASlashCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
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
	//Cast<USlashAbilitySystemComponent>(SlashPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();

	//This is the place we place an if check and not an assert as in the client all three player controllers are not present
	/*if (ASlashPlayerController* SlashPlayerController =  Cast<ASlashPlayerController>(GetController()))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerController->GetHUD());
		if (AuraHUD)
		{
			AuraHUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}*/
	//InitializeDefaultAttributes();
}
