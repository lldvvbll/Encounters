// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/GameStateBase.h"
#include "EncGameState.generated.h"

UCLASS()
class ENCOUNTERS_API AEncGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void SetReadyState(bool bReady);
	bool IsReadyState() const;

private:
	UPROPERTY(Transient)
	bool bGameReady;
};
