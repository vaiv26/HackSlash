// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "SlashAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	 GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()
 
	FEffectProperties(){}
 
	FGameplayEffectContextHandle EffectContextHandle;
 
	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
 
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
 
	UPROPERTY()
	AController* SourceController = nullptr;
 
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;
 
	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
 
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
 
	UPROPERTY()
	AController* TargetController = nullptr;
 
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};
 

/**
 * 
 */
UCLASS()
class HACKSLASH_API USlashAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	USlashAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(USlashAttributeSet, Health);
 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Vital Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(USlashAttributeSet, MaxHealth);
 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(USlashAttributeSet, Mana);
 
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Vital Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(USlashAttributeSet, MaxMana);
	
	/*
  * Meta Attributes
  */
 
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(USlashAttributeSet, IncomingDamage);
 
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
 
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
 
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
 
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

private:
 
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
};
