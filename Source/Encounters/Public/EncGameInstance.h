// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/GameInstance.h"
#include "EncGameInstance.generated.h"

class UDataTable;
struct FCharacterAbilityData;
struct FLevelUpPointData;
struct FWeaponData;
struct FShieldData;
struct FArmorData;

UCLASS()
class ENCOUNTERS_API UEncGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEncGameInstance();

	FCharacterAbilityData* GetCharacterAbilityData(int32 Point) const;

private:
	UPROPERTY()
	UDataTable* CharacterAbilityTable;

	UPROPERTY()
	UDataTable* LevelUpPointTable;
};
