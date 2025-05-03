// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SlashCharacterBase.h"
#include "SlashCharacter.generated.h"

class UGameplayEffect;
/**
 * 
 */
UCLASS()
class HACKSLASH_API ASlashCharacter : public ASlashCharacterBase
{
	GENERATED_BODY()

public:
	ASlashCharacter();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:
	virtual void InitAbilityActorInfo() override;

private:

	UPROPERTY(VisibleAnywhere, Category = Camera)
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = Camera)
	class UCameraComponent* FollowCamera;
	
};
