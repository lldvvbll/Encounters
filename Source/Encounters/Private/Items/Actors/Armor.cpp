// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Armor.h"
#include "Items/DataAssets/ArmorDataAsset.h"

AArmor::AArmor()
{
	StMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = StMeshComp;
	StMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

float AArmor::GetUseStaminaOnRolling() const
{
	TWeakObjectPtr<UArmorDataAsset> DataAsset = Cast<UArmorDataAsset>(ItemDataAsset);
	if (!DataAsset.IsValid())
		return -1.0;

	return DataAsset->Stamina;
}
