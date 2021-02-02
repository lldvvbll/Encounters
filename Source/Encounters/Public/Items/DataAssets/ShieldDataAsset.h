// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/DataAssets/ItemDataAsset.h"
#include "ShieldDataAsset.generated.h"

UCLASS()
class ENCOUNTERS_API UShieldDataAsset : public UItemDataAsset
{
	GENERATED_BODY()

public:
	UShieldDataAsset();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float DamageReduction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float GuardSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Option)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Actor)
	TSubclassOf<AActor> ItemActor;
};
