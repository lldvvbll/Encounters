// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/EncStage.h"

void UEncStage::Init(const FPrimaryAssetId& NewDataAssetId)
{
	DataAssetId = NewDataAssetId;
}