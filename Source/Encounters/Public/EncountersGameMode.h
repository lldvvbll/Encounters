// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/GameModeBase.h"
#include "EncountersGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API AEncountersGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AEncountersGameMode();

	virtual void PostLogin(APlayerController* NewPlayer) override;
};
