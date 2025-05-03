// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "SlashAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class HACKSLASH_API USlashAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
 
	static USlashAssetManager& Get();
 
protected:
 
	virtual void StartInitialLoading() override;
	
};
