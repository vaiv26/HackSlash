// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SlashCharacterBase.generated.h"

UCLASS(Abstract)
class HACKSLASH_API ASlashCharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASlashCharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<USkeletalMeshComponent> Weapon;

};
