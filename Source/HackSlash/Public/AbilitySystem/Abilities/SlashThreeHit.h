// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/SlashGameplayAbility.h"
#include "SlashThreeHit.generated.h"

/**
 * 
 */
UCLASS()
class HACKSLASH_API USlashThreeHit : public USlashGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category="Animation")
	void NotifyAnimation();
	
};
