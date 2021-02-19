// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Armor.generated.h"

class UItemDataAsset;
class UArmorDataAsset;

UCLASS()
class ENCOUNTERS_API AArmor : public AEquipment
{
	GENERATED_BODY()
	
public:
	AArmor();

	virtual void SetItemDataAsset(UItemDataAsset* DataAsset) override;
	const UArmorDataAsset* GetArmorDataAsset() const;

	float GetDefense() const;
	float GetUseStaminaOnRolling() const;

protected:
	UPROPERTY()
	UArmorDataAsset* ArmorDataAsset;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* StMeshComp;
};
