// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "EncStructures.generated.h"

UENUM(BlueprintType)
enum class EPocketType : uint8
{
	Default,
	Weapon,
	Shield,
	Armor,
};

UENUM(BlueprintType)
enum class EPlayerStateAttribute : uint8
{
	Level,
	Point,
	Strength,
	Agility,
	Vitality,
	Endurance,
};

USTRUCT(BlueprintType)
struct FSavePlayerStateData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Point;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Agility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Vitality;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Endurance;
};

USTRUCT(BlueprintType)
struct FSaveItemData
{
	GENERATED_BODY()

public:
	FSaveItemData();
	FSaveItemData(FPrimaryAssetId NewAssetId, EPocketType NewPocketType, int32 NewCount);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FPrimaryAssetId AssetId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EPocketType PocketType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Count;
};
