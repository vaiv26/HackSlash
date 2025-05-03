// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SlashAIController.generated.h"

class UBehaviorTreeComponent;
/**
 * 
 */
UCLASS()
class HACKSLASH_API ASlashAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASlashAIController();
protected:
 
	UPROPERTY()
	TObjectPtr<UBehaviorTreeComponent> BehaviorTreeComponent;
	
};
