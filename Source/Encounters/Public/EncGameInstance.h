// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/GameInstance.h"
#include "EncStructures.h"
#include "DataStructures.h"
#include "EncGameInstance.generated.h"

class UDataTable;
class UEncItem;

USTRUCT(BlueprintType)
struct FDefaultItem
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FPrimaryAssetId AssetId;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	EPocketType PocketType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Count;
};

USTRUCT(BlueprintType)
struct FDefaultPlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Level;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Strength;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Agility;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Vitality;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int32 Endurance;
};

UCLASS()
class ENCOUNTERS_API UEncGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEncGameInstance();

	FCharacterAbilityData* GetCharacterAbilityData(int32 Point) const;

	const TArray<FDefaultItem>& GetDefaultItems() const;
	const FDefaultPlayerState& GetDefaultPlayerState() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	TArray<FDefaultItem> DefaultItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	FDefaultPlayerState DefaultPlayerState;

private:
	UPROPERTY()
	UDataTable* CharacterAbilityTable;

	UPROPERTY()
	UDataTable* LevelUpPointTable;
};
