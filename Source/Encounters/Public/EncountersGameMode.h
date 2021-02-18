// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/GameModeBase.h"
#include "EncountersGameMode.generated.h"

class ASpawnBox;
class UStageDataAsset;
class APlayerCharacter;
class ANpcCharacter;

UCLASS()
class ENCOUNTERS_API AEncountersGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEncountersGameMode();

	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(Exec, Category = ExecFunctions)
	void exec_SpawnEnemy() const;

private:
	void StartStage();
	void SpawnEnemies();

	void OnEnemyDead(ANpcCharacter* DeadEnemy);

private:
	UPROPERTY(VisibleAnywhere, Category = DataAsset, Meta = (AllowPrivateAccess = true))
	UStageDataAsset* StageDataAsset;

	UPROPERTY()
	TArray<ASpawnBox*> SpawnBoxes;

	UPROPERTY()
	TArray<ANpcCharacter*> Enemies;
};
