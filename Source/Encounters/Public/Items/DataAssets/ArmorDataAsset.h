// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/DataAssets/ItemDataAsset.h"
#include "ArmorDataAsset.generated.h"

UCLASS()
class ENCOUNTERS_API UArmorDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:
	UArmorDataAsset();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float Defense;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Class)
	TSubclassOf<AActor> ItemActorClass;
};
