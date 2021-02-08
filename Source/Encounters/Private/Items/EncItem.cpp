// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/EncItem.h"
#include "Items/DataAssets/ItemDataAsset.h"
#include "EncAssetManager.h"

void UEncItem::Init(const FPrimaryAssetId& NewDataAssetId, int32 NewCount)
{
	DataAssetId = NewDataAssetId;
	Count = NewCount;
}

const FPrimaryAssetId& UEncItem::GetDataAssetId() const
{
	return DataAssetId;
}

UItemDataAsset* UEncItem::GetDataAsset() const
{
	return UEncAssetManager::Get().GetDataAsset<UItemDataAsset>(DataAssetId);
}

int32 UEncItem::GetCount() const
{
	return Count;
}
