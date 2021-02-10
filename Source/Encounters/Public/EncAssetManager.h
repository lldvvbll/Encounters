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
	static const FPrimaryAssetType WeaponItemType;
	static const FPrimaryAssetType ShieldItemType;
	static const FPrimaryAssetType ArmorItemType;

	static const FPrimaryAssetType EnemyType;

public:
	static UEncAssetManager& Get();

	template <typename T>
	T* GetDataAsset(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true)
	{
		T* DataAsset = GetPrimaryAssetObject<T>(PrimaryAssetId);
		if (DataAsset == nullptr)
		{
			DataAsset = ForceLoadDataAsset<T>(PrimaryAssetId, bLogWarning);
		}

		return DataAsset;
	}

	template <typename T>
	T* ForceLoadDataAsset(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true)
	{
		T* LoadedDataAsset = Cast<T>(GetPrimaryAssetPath(PrimaryAssetId).TryLoad());

		if (bLogWarning && LoadedDataAsset == nullptr)
		{
			LOG(Warning, TEXT("Failed to load Asset for identifier %s!"), *PrimaryAssetId.ToString());
		}

		return LoadedDataAsset;
	}
};
