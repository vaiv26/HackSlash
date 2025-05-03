// Fill out your copyright notice in the Description page of Project Settings.


#include "SlashAssetManager.h"

#include "SlashGameplayTags.h"

USlashAssetManager& USlashAssetManager::Get()
{
	check(GEngine);
 	
	USlashAssetManager* SlashAssetManager = Cast<USlashAssetManager>(GEngine->AssetManager);
	return *SlashAssetManager;
}

void USlashAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();
 
	FSlashGameplayTags::InitializeNativeGameplayTags();
}
