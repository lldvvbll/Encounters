// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/SaveGame.h"
#include "EncSaveGame.generated.h"

UCLASS()
class ENCOUNTERS_API UEncSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UEncSaveGame();

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Point;

	UPROPERTY()
	int32 Strength;

	UPROPERTY()
	int32 Agility;

	UPROPERTY()
	int32 Vitality;

	UPROPERTY()
	int32 Endurance;
};
