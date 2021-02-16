// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/DataAssets/StageDataAsset.h"
#include "EncAssetManager.h"

UStageDataAsset::UStageDataAsset()
{
	StageType = UEncAssetManager::NormalStageType;
}

FPrimaryAssetId UStageDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(StageType, GetFName());
}
