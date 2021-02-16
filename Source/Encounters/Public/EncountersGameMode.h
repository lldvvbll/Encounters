// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/GameModeBase.h"
#include "EncountersGameMode.generated.h"

class ASpawnBox;

UCLASS()
class ENCOUNTERS_API AEncountersGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEncountersGameMode();

	virtual void StartPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

	UFUNCTION(Exec, Category = ExecFunctions)
	void SpawnEnemy() const;

private:
	UPROPERTY(Transient)
	TArray<ASpawnBox*> SpawnBoxes;
};
