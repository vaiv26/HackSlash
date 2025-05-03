// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/SlashThreeHit.h"

void USlashThreeHit::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void USlashThreeHit::NotifyAnimation()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;
	

	//TODO: Give the a Gameplay Effect Spec for causing Damage.
}
