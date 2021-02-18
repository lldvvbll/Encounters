// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Engine/GameInstance.h"
#include "EncStructures.h"
#include "DataStructures.h"
#include "EncGameInstance.generated.h"

class UDataTable;
class UStageDataAsset;

UCLASS()
class ENCOUNTERS_API UEncGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UEncGameInstance();

	FCharacterAbilityData* GetCharacterAbilityData(int32 Point) const;
	int32 GetLevelUpPoint(int32 CurLevel) const;

	const TArray<FSaveItemData>& GetDefaultItems() const;
	const FSavePlayerStateData& GetDefaultPlayerState() const;
	const TArray<FPrimaryAssetId>& GetStageAssetIds() const;

	void StartNewGame();
	void ContinueGame();
	void GoToNextStage();

	FPrimaryAssetId GetCurrentStageDataAssetId() const;
	int32 GetCurrentStageIndex() const;
	bool IsLastStage() const;

private:
	void GoToStage(int32 Index);

public:
	static const FString SaveGameSlotName;
	static const int32 SaveGameUserIndex;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	TArray<FSaveItemData> DefaultItems;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = DefaultSetting)
	FSavePlayerStateData DefaultPlayerState;

	UPROPERTY(EditDefaultsOnly, Category = Stage)
	TArray<FPrimaryAssetId> StageAssetIds;

private:
	UPROPERTY()
	UDataTable* CharacterAbilityTable;

	UPROPERTY()
	UDataTable* LevelUpPointTable;

	UPROPERTY()
	int32 CurrentStageIndex;
};
