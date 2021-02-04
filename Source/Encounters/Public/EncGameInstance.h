// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/GameInstance.h"
#include "EncStructures.h"
#include "DataStructures.h"
#include "EncGameInstance.generated.h"

class UDataTable;

UCLASS()
class ENCOUNTERS_API UEncGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEncGameInstance();

	FCharacterAbilityData* GetCharacterAbilityData(int32 Point) const;

	const TArray<FSaveItemData>& GetDefaultItems() const;
	const FSavePlayerStateData& GetDefaultPlayerState() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	TArray<FSaveItemData> DefaultItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	FSavePlayerStateData DefaultPlayerState;

private:
	UPROPERTY()
	UDataTable* CharacterAbilityTable;

	UPROPERTY()
	UDataTable* LevelUpPointTable;
};
