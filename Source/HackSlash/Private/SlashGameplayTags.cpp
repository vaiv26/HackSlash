// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashGameplayTags.h"

#include "GameplayTagsManager.h"


FSlashGameplayTags FSlashGameplayTags::GameplayTags;

void FSlashGameplayTags::InitializeNativeGameplayTags()
{
	/*
	 *Animation Montage
	 */
	GameplayTags.Event_Montage_Attack_MeleeStart = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Montage.Attack.MeleeStart"),
		FString("Montage start tag")
		);
	
	GameplayTags.Event_Montage_Attack_MeleeEnd = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Event.Montage.Attack.MeleeEnd"),
		FString("Montage end tag")
		);
	
	/*
  * Input Tags
  */
 	
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.LMB"),
		FString("Input Tag for Left Mouse Button")
		);
 
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.RMB"),
		FString("Input Tag for Right Mouse Button")
		);
 
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
		);

	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
		);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
		);
	
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(
		 FName("Damage"),
		 FString("Damage")
		 );
	
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(
		 FName("Effects.HitReact"),
		 FString("Tag granted when Hit Reacting")
		 );

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		 FName("Abilities.Attack"),
		 FString("Attack Ability Tag")
		 );
	
		 
	GameplayTags.Cooldown_LightAttack = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Cooldown.Attack.LightAttack"),
		FString("Cooldown Ability Tag")
		);
}
