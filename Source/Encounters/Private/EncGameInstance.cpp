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

void UEncGameInstance::StartNewGame()
{
	return_if(StageAssetIds.Num() == 0);

	UStageDataAsset* StageDataAsset = UEncAssetManager::Get().GetDataAsset<UStageDataAsset>(StageAssetIds[0]);
	return_if(StageDataAsset == nullptr);

	UGameplayStatics::DeleteGameInSlot(UEncGameInstance::SaveGameSlotName, UEncGameInstance::SaveGameUserIndex);
	UGameplayStatics::OpenLevel(GetWorld(), StageDataAsset->LevelAssetId.PrimaryAssetName);
}

void UEncGameInstance::ContinueGame()
{
	return_if(StageAssetIds.Num() == 0);

	UStageDataAsset* StageDataAsset = UEncAssetManager::Get().GetDataAsset<UStageDataAsset>(StageAssetIds[0]);
	return_if(StageDataAsset == nullptr);

	UGameplayStatics::OpenLevel(GetWorld(), StageDataAsset->LevelAssetId.PrimaryAssetName);
}

FPrimaryAssetId UEncGameInstance::GetCurrentStageDataAssetId() const
{
	return_if(StageAssetIds.Num() == 0, FPrimaryAssetId());

	return StageAssetIds[CurrentStageIndex];
}

int32 UEncGameInstance::GetCurrentStageIndex() const
{
	return CurrentStageIndex;
}
