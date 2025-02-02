// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/DataTable.h"
#include "DataStructures.generated.h"

USTRUCT(BlueprintType)
struct FCharacterAbilityData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Strength")
	int32 AttackPower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agility")
	float RollingSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Agility")
	float RollingVelocityRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vitality")
	float HP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Endurance")
	float Stamina;
};

USTRUCT(BlueprintType)
struct FLevelUpPointData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Point")
	int32 Point;
};
