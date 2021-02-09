// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/DataAssets/NpcDataAsset.h"
#include "EncAssetManager.h"

UNpcDataAsset::UNpcDataAsset()
{
	NpcType = UEncAssetManager::EnemyType;
}

FPrimaryAssetId UNpcDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(NpcType, GetFName());
}
