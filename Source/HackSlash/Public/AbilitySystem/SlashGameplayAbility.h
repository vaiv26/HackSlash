// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SlashGameplayAbility.generated.h"

USTRUCT(BlueprintType)
struct FHitActorData
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* HitActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitDirection;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector HitLocation;

	// Constructor
	FHitActorData()
		: HitActor(nullptr)
		, HitDirection(FVector::ZeroVector),HitLocation(FVector::ZeroVector)
	
	{
	}

	FHitActorData(AActor* InActor, const FVector& InDirection, const FVector& InLocation)
	: HitActor(InActor)
	, HitDirection(InDirection), HitLocation(InLocation)
	{
	}

	// Equality operator for TArray functions like AddUnique
	bool operator==(const FHitActorData& Other) const
	{
		return HitActor == Other.HitActor;
	}
};


/**
 * 
 */
UCLASS()
class HACKSLASH_API USlashGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Damage")
	float Damage;
	
	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor, const FVector HitDirection);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FGameplayTag DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
	TArray<FHitActorData> HitActors;
};
