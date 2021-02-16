// Fill out your copyright notice in the Description page of Project Settings.


#include "EncGameInstance.h"
#include "Engine/DataTable.h"
#include "DataStructures.h"
#include "Items/EncItem.h"
#include "EncAssetManager.h"
#include "Stage/DataAssets/StageDataAsset.h"

const FString UEncGameInstance::SaveGameSlotName = TEXT("Default");
const int32 UEncGameInstance::SaveGameUserIndex = 0;

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

const TArray<FSaveItemData>& UEncGameInstance::GetDefaultItems() const
{
	return DefaultItems;
}

const FSavePlayerStateData& UEncGameInstance::GetDefaultPlayerState() const
{
	return DefaultPlayerState;
}

const TArray<FPrimaryAssetId>& UEncGameInstance::GetStageAssetIds() const
{
	return StageAssetIds;
}

UStageDataAsset* UEncGameInstance::GetStageDataAssetByIndex(int32 Index) const
{
	return_if(Index < 0, nullptr);
	return_if(StageAssetIds.Num() <= Index, nullptr);

	return UEncAssetManager::Get().GetDataAsset<UStageDataAsset>(StageAssetIds[Index]);
}

int32 UEncGameInstance::GetCurretnStageIndex() const
{
	return CurrentStageIndex;
}

void UEncGameInstance::SetCurrentStageIndex(int32 Index)
{
	CurrentStageIndex = Index;
}
