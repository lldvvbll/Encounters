// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Equipment.h"
#include "Items/DataAssets/ItemDataAsset.h"

AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AEquipment::SetItemDataAsset(UItemDataAsset* DataAsset)
{
	ItemDataAsset = DataAsset;
}

const UItemDataAsset* AEquipment::GetItemDataAsset() const
{
	return ItemDataAsset;
}

FVector AEquipment::GetAttachOffset() const
{
	return AttachOffset;
}

FRotator AEquipment::GetAttachRotator() const
{
	return AttachRotator;
}
