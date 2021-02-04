// Fill out your copyright notice in the Description page of Project Settings.


#include "EncGameInstance.h"
#include "Engine/DataTable.h"
#include "DataStructures.h"
#include "Items/EncItem.h"

UEncGameInstance::UEncGameInstance()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_CHARABILITY(
		TEXT("/Game/Encounters/Data/DT_CharacterAbility.DT_CharacterAbility"));
	return_if(!DT_CHARABILITY.Succeeded());

	CharacterAbilityTable = DT_CHARABILITY.Object;
	return_if(CharacterAbilityTable->GetRowMap().Num() <= 0);

	static ConstructorHelpers::FObjectFinder<UDataTable> DT_LEVELUPPOINT(
		TEXT("/Game/Encounters/Data/DT_LevelUpPoint.DT_LevelUpPoint"));
	return_if(!DT_LEVELUPPOINT.Succeeded());

	LevelUpPointTable = DT_LEVELUPPOINT.Object;
	return_if(LevelUpPointTable->GetRowMap().Num() <= 0);
}

FCharacterAbilityData* UEncGameInstance::GetCharacterAbilityData(int32 Point) const
{
	return CharacterAbilityTable->FindRow<FCharacterAbilityData>(*FString::FromInt(Point), TEXT(""));
}

const TArray<FDefaultItem>& UEncGameInstance::GetDefaultItems() const
{
	return DefaultItems;
}

const FDefaultPlayerState& UEncGameInstance::GetDefaultPlayerState() const
{
	return DefaultPlayerState;
}
