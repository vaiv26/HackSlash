// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SlashPlayerController.generated.h"

class USlashAbilitySystemComponent;
class USlashInputConfig;
struct FGameplayTag;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
/**
 * 
 */
UCLASS()
class HACKSLASH_API ASlashPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASlashPlayerController();
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputMappingContext> SlashContext;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	TObjectPtr<UInputAction> LookAround;

	void Move(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
 
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<USlashInputConfig> InputConfig;

	
	UPROPERTY()
	TObjectPtr<USlashAbilitySystemComponent> AuraAbilitySystemComponent;
 
	USlashAbilitySystemComponent* GetASC();
	
};
