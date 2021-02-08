// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Armor.h"
#include "Items/DataAssets/ArmorDataAsset.h"

AArmor::AArmor()
{
	StMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = StMeshComp;
	StMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

void AArmor::SetItemDataAsset(UItemDataAsset* DataAsset)
{
	Super::SetItemDataAsset(DataAsset);

	ArmorDataAsset = Cast<UArmorDataAsset>(DataAsset);
}

const UArmorDataAsset* AArmor::GetArmorDataAsset() const
{
	return ArmorDataAsset;
}

float AArmor::GetUseStaminaOnRolling() const
{
	return_if(ArmorDataAsset == nullptr, -1.0f);

	return ArmorDataAsset->Stamina;
}
