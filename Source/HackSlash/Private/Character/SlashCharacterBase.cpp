// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashCharacterBase.h"

#include "AbilitySystemComponent.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ASlashCharacterBase::ASlashCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	Weapon->SetupAttachment(GetMesh(),FName("WeaponHandSocket"));
	Weapon->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Weapon->SetCollisionResponseToAllChannels(ECR_Block);
}

UAbilitySystemComponent* ASlashCharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* ASlashCharacterBase::GetAttributeSet() const
{
	return AttributeSet;
}

UAnimMontage* ASlashCharacterBase::GetHitReactMontage_Implementation(FVector HitDirection)
{
	const FVector TargetRightVector = GetActorRightVector();
	float DotProduct = FVector::DotProduct(HitDirection, TargetRightVector);
	if (DotProduct > 0.0f)
	{
		return HitRightReactMontage;
	}
	return HitLeftReactMontage;
}

void ASlashCharacterBase::Die()
{
	Weapon->DetachFromComponent(FDetachmentTransformRules(EDetachmentRule::KeepWorld, true));
	MulticastHandleDeath();
}

FVector ASlashCharacterBase::GetCombatTipSocketLocation_Implementation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTipSocketName);
}

FVector ASlashCharacterBase::GetCombatTailSocketLocation_Implementation()
{
	check(Weapon);
	return Weapon->GetSocketLocation(WeaponTailSocketName);
}

bool ASlashCharacterBase::IsDead_Implementation() const
{
	return bDead;
}

AActor* ASlashCharacterBase::GetAvatar_Implementation()
{
	return this;
}

UNiagaraSystem* ASlashCharacterBase::GetHitEffect_Implementation()
{
	return HitEffect;
}

void ASlashCharacterBase::MulticastHandleDeath_Implementation()
{
	Weapon->SetSimulatePhysics(true);
	Weapon->SetEnableGravity(true);
	Weapon->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
 
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->SetEnableGravity(true);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	GetMesh()->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
 
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bDead = true;
}

// Called when the game starts or when spawned
void ASlashCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlashCharacterBase::InitAbilityActorInfo()
{
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

