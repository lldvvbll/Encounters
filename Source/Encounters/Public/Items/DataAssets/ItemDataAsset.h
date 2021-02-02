// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/DataAsset.h"
#include "ItemDataAsset.generated.h"

UCLASS(Abstract, BlueprintType)
class ENCOUNTERS_API UItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
	FPrimaryAssetType ItemType;

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;
};
