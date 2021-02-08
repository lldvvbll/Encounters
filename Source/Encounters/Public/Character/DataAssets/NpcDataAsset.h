// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/DataAsset.h"
#include "NpcDataAsset.generated.h"

UCLASS()
class ENCOUNTERS_API UNpcDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UNpcDataAsset();

	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Type)
	FPrimaryAssetType NpcType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float RollingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float RollingVelocityRate;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Ability)
	float DetectRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = ActorClass)
	TSubclassOf<AActor> NpcActorClass;
};
