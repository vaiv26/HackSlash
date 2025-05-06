// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/SlashEnemy.h"

#include "SlashGameplayTags.h"
#include "AbilitySystem/SlashAbilitySystemComponent.h"
#include "AbilitySystem/SlashAbilitySystemLibrary.h"
#include "AbilitySystem/SlashAttributeSet.h"
#include "AI/SlashAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widget/SlashUserWidget.h"

ASlashEnemy::ASlashEnemy()
{
	AbilitySystemComponent = CreateDefaultSubobject<USlashAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	AttributeSet = CreateDefaultSubobject<USlashAttributeSet>("AttributeSet");

	HealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	HealthBar->SetupAttachment(GetRootComponent());

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = true;
}

void ASlashEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!HasAuthority()) return;
	SlashAIController = Cast<ASlashAIController>(NewController);
	SlashAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	SlashAIController->RunBehaviorTree(BehaviorTree);
	SlashAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), false);
	SlashAIController->GetBlackboardComponent()->SetValueAsBool(FName("RangedAttacker"), CharacterClass != ECharacterClass::Warrior);
}

void ASlashEnemy::SetCombatTarget_Implementation(AActor* InCombatTarget)
{
	CombatTarget = InCombatTarget;
}

AActor* ASlashEnemy::GetCombatTarget_Implementation() const
{
	return CombatTarget;
}

void ASlashEnemy::StopEnemyBehaviourTree_Implementation()
{
	if (UBrainComponent* BrainComponent = SlashAIController->GetBrainComponent())
	{
		BrainComponent->StopLogic("User requested stop");
	}
}

void ASlashEnemy::StartEnemyBehaviourTree_Implementation()
{
	if (UBrainComponent* BrainComponent = SlashAIController->GetBrainComponent())
	{
		BrainComponent->StartLogic();
	}
}

void ASlashEnemy::BeginPlay()
{
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	check(AbilitySystemComponent);
	InitAbilityActorInfo();
	if (HasAuthority())
	{
		USlashAbilitySystemLibrary::GiveStartupAbilities(this, AbilitySystemComponent, CharacterClass);
	}

	if (USlashUserWidget* AuraUserWidget = Cast<USlashUserWidget>(HealthBar->GetUserWidgetObject()))
	{
		AuraUserWidget->SetWidgetController(this);
	}
 	
	if (const USlashAttributeSet* SlashAS = Cast<USlashAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SlashAS->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			}
		);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(SlashAS->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
		);

		AbilitySystemComponent->RegisterGameplayTagEvent(FSlashGameplayTags::Get().Effects_HitReact, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this,&ASlashEnemy::HitReactTagChanged);
 
		OnHealthChanged.Broadcast(SlashAS->GetHealth());
		OnMaxHealthChanged.Broadcast(SlashAS->GetMaxHealth());
	}
}

void ASlashEnemy::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	InitializeDefaultAttributes(); 
}

void ASlashEnemy::InitializeDefaultAttributes() const
{
	USlashAbilitySystemLibrary::InitializeDefaultAttributes(this, CharacterClass, 1.0f, AbilitySystemComponent);
}

void ASlashEnemy::Die()
{
	SetLifeSpan(LifeSpan);
	Super::Die();
}

void ASlashEnemy::HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bHitReacting = NewCount > 0;
	GetCharacterMovement()->MaxWalkSpeed = bHitReacting ? 0.f : BaseWalkSpeed;
	if (SlashAIController && SlashAIController->GetBlackboardComponent())
	{
		SlashAIController->GetBlackboardComponent()->SetValueAsBool(FName("HitReacting"), bHitReacting);
	}
}
