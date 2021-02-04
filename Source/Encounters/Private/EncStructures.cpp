// Fill out your copyright notice in the Description page of Project Settings.


#include "EncStructures.h"

FSaveItemData::FSaveItemData()
{
}

FSaveItemData::FSaveItemData(FPrimaryAssetId NewAssetId, EPocketType NewPocketType, int32 NewCount)
{
	AssetId = NewAssetId;
	PocketType = NewPocketType;
	Count = NewCount;
}
