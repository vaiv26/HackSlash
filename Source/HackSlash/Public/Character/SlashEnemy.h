// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "Character/SlashCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "SlashEnemy.generated.h"

class UBehaviorTree;
class ASlashAIController;
class UWidgetComponent;
/**
 * 
 */
UCLASS()
class HACKSLASH_API ASlashEnemy : public ASlashCharacterBase
{
	GENERATED_BODY()

public:
	ASlashEnemy();
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;
 
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;
	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UWidgetComponent> HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
 
	UPROPERTY()
	TObjectPtr<ASlashAIController> SlashAIController;
	
};
