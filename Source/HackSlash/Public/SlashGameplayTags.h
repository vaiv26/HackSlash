// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  Slash Gameplay Tags
 *
 *  Singleton containing native gameplay tags
 */

struct FSlashGameplayTags
{
public:
	static FSlashGameplayTags& Get() {return GameplayTags;}
	static void InitializeNativeGameplayTags();
	
	//Anim montage tag
	FGameplayTag Event_Montage_Attack_MeleeStart;
	FGameplayTag Event_Montage_Attack_MeleeEnd;
	//Inputs
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;

	FGameplayTag Damage;
	FGameplayTag Effects_HitReact;

	FGameplayTag Abilities_Attack;
private:
	static FSlashGameplayTags GameplayTags;
};
