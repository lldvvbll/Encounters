// Fill out your copyright notice in the Description page of Project Settings.


#include "EncAssetManager.h"
#include "Items/DataAssets/ItemDataAsset.h"

const FPrimaryAssetType	UEncAssetManager::WeaponItemType = TEXT("Weapon");
const FPrimaryAssetType	UEncAssetManager::ShieldItemType = TEXT("Shield");
const FPrimaryAssetType	UEncAssetManager::ArmorItemType = TEXT("Armor");

const FPrimaryAssetType UEncAssetManager::HostileNpcType = TEXT("HostileNpc");

UEncAssetManager& UEncAssetManager::Get()
{
	UEncAssetManager* This = Cast<UEncAssetManager>(GEngine->AssetManager);

	if (This != nullptr)
	{
		return *This;
	}
	else
	{
		LOG(Fatal, TEXT("Invalid AssetManager in DefaultEngine.ini, must be UEncAssetManager!"));
		return *NewObject<UEncAssetManager>();
	}
}
