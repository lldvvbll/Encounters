// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "UObject/NoExportTypes.h"
#include "EncStage.generated.h"

class UStageDataAsset;

UCLASS(Blueprintable)
class ENCOUNTERS_API UEncStage : public UObject
{
	GENERATED_BODY()

public:
	void StartStage(const FPrimaryAssetId& NewDataAssetId);

protected:
	void SpawnEnemy();

protected:
	UPROPERTY(VisibleAnywhere, Category = DataAsset)
	UStageDataAsset* StageDataAsset;
};
