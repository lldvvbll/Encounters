// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/DataAsset.h"
#include "StageDataAsset.generated.h"

UCLASS()
class ENCOUNTERS_API UStageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UStageDataAsset();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Type)
	FPrimaryAssetType StageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Level)
	FPrimaryAssetId LevelAssetId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Enemy)
	TMap<FPrimaryAssetId, int32> EnemyMap;
};
