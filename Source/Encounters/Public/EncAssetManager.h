// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/AssetManager.h"
#include "EncAssetManager.generated.h"

class UItemDataAsset;

UCLASS()
class ENCOUNTERS_API UEncAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static const FPrimaryAssetType	WeaponItemType;
	static const FPrimaryAssetType	ShieldItemType;
	static const FPrimaryAssetType	ArmorItemType;


	static UEncAssetManager& Get();

	UItemDataAsset* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
