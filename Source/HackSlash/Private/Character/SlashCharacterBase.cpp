// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashCharacterBase.h"

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

