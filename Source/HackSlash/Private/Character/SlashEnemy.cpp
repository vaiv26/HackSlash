// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashEnemy.h"
#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "AbilitySystem/SlashAttributeSet.h"

ASlashEnemy::ASlashEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<USlashAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<USlashAttributeSet>("AttributeSet");
}

void ASlashEnemy::BeginPlay()
{
	Super::BeginPlay();
	check(AbilitySystemComponent);
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}
