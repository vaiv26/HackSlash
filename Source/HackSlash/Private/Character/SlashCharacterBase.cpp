// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/SlashAbilitySystemComponent.h"

// Sets default values
ASlashCharacterBase::ASlashCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));

}

UAbilitySystemComponent* ASlashCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASlashCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

// Called when the game starts or when spawned
void ASlashCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlashCharacterBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ASlashCharacterBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(PrimaryVitalAttributes, 1.f);
	ApplyEffectToSelf(DefaultVitalAttributes, 1.f);
}

void ASlashCharacterBase::AddCharacterAbilities()
{
	USlashAbilitySystemComponent* SlashASC = CastChecked<USlashAbilitySystemComponent>(AbilitySystemComponent);
	if (!HasAuthority()) return;
 
	SlashASC->AddCharacterAbilities(StartupAbilities);
}

