// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SlashGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void USlashGameplayAbility::CauseDamage(AActor* TargetActor, const FVector HitDirection)
{
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, Damage);
	// Get the effect context from the spec
	FGameplayEffectContextHandle ContextHandle = DamageSpecHandle.Data.Get()->GetEffectContext();
    
	// Create a hit result with your direction
	FHitResult HitResult;
	HitResult.ImpactNormal = -HitDirection; // Negative because impact normal points back to source
	HitResult.Location = TargetActor->GetActorLocation();
    
	// Add the hit result to the context
	ContextHandle.AddHitResult(HitResult);
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}


