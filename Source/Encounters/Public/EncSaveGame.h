// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/SaveGame.h"
#include "EncStructures.h"
#include "EncSaveGame.generated.h"

UCLASS()
class ENCOUNTERS_API UEncSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UEncSaveGame();

	void Copy(UEncSaveGame* Src);

public:
	UPROPERTY()
	FSavePlayerStateData PlayerState;

	UPROPERTY()
	TArray<FSaveItemData> Items;
};
