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
	void SpawnEnemy() const;
	
	UFUNCTION(Exec, Category = ExecFunctions)
	void SetAttr(const FString& Attr, int32 Value) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void DrawDebugAll(bool bDraw) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void DrawDebugDetect(bool bDraw) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void DrawDebugWeapon(bool bDraw) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void DrawDebugGuard(bool bDraw) const;

	UFUNCTION(Exec, Category = ExecFunctions)
	void DrawDebugAvoid(bool bDraw) const;

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
