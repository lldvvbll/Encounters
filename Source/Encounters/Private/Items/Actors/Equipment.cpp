// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Equipment.h"

AEquipment::AEquipment()
{
	PrimaryActorTick.bCanEverTick = false;

}

FVector AEquipment::GetAttachOffset() const
{
	return AttachOffset;
}

FRotator AEquipment::GetAttachRotator() const
{
	return AttachRotator;
}

void AEquipment::SetItemDataAsset(const TWeakObjectPtr<UItemDataAsset>& DataAsset)
{
	ItemDataAsset = DataAsset;
}

const TWeakObjectPtr<UItemDataAsset>& AEquipment::GetItemDataAsset() const
{
	return ItemDataAsset;
}
