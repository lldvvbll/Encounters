// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/DataAssets/ItemDataAsset.h"
#include "WeaponDataAsset.generated.h"

UCLASS()
class ENCOUNTERS_API UWeaponDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:
	UWeaponDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float AttackSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActorClass)
	TSubclassOf<AActor> ItemActorClass;
};
