// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/EncStage.h"
#include "Stage/DataAssets/StageDataAsset.h"
#include "EncAssetManager.h"
#include "EncountersGameMode.h"

void UEncStage::StartStage(const FPrimaryAssetId& NewDataAssetId)
{
	StageDataAsset = UEncAssetManager::Get().GetDataAsset<UStageDataAsset>(NewDataAssetId);
	return_if(StageDataAsset == nullptr);


}

void UEncStage::SpawnEnemy()
{
	for (auto& Pair : StageDataAsset->EnemyMap)
	{
		FPrimaryAssetId& EnemyDataAssetId = Pair.Key;
		int32& Count = Pair.Value;
	}
}
