// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/SlashAbilitySystemLibrary.h"
#include "AbilitySystem/SlashGameplayAbility.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Game/SlashGameModeBase.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "PlayerController/SlashPlayerState.h"
#include "UI/HUD/SlashHUD.h"
#include "UI/WidgetController/SlashWidgetController.h"

UOverlayWidgetController* USlashAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ASlashHUD* SlashHUD = Cast<ASlashHUD>(PC->GetHUD()))
		{
			ASlashPlayerState* PS = PC->GetPlayerState<ASlashPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return SlashHUD->GetOverlayWidgetController(WidgetControllerParams);
		}
	}
	return nullptr;
}

void USlashAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject,
	ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	ASlashGameModeBase* SlashGameMode = Cast<ASlashGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (SlashGameMode == nullptr) return;
 
	AActor* AvatarActor = ASC->GetAvatarActor();
 
	UCharacterClassInfo* CharacterClassInfo = SlashGameMode->CharacterClassInfo;
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
 
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());
 
	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void USlashAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC,
	ECharacterClass CharacterClass)
{
	ASlashGameModeBase* SlashGameMode = Cast<ASlashGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (SlashGameMode == nullptr) return;
 
	UCharacterClassInfo* CharacterClassInfo = SlashGameMode->CharacterClassInfo;
	if (CharacterClassInfo == nullptr) return;
	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
	{
		if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor()))
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass);
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

bool USlashAbilitySystemLibrary::GetLivePlayers( const AActor* OverlappingActor)
{
	if (OverlappingActor->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(OverlappingActor))
	{
		return true;
	}
	return false;
}

void USlashAbilitySystemLibrary::AddOrUpdateHitActor(TArray<FHitActorData>& HitActors, AActor* Actor, FVector Direction, FVector HitLocation)
{
	{
		// Check if actor already exists
		for (FHitActorData& ExistingData : HitActors)
		{
			if (ExistingData.HitActor == Actor)
			{
				// Update direction for existing actor
				ExistingData.HitDirection = Direction;
				return;
			}
		}
    
		// Actor doesn't exist, add it
		HitActors.Add(FHitActorData(Actor, Direction, HitLocation));
	}
}
