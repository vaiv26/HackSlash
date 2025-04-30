// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController/SlashPlayerState.h"

#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "AbilitySystem/SlashAttributeSet.h"

ASlashPlayerState::ASlashPlayerState()
{
	NetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<USlashAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<USlashAttributeSet>("AttributeSet");
}

UAbilitySystemComponent* ASlashPlayerState::GetAbilitySystemComponent() const
{
	return	AbilitySystemComponent;
}

UAttributeSet* ASlashPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
