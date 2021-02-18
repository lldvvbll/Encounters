// Fill out your copyright notice in the Description page of Project Settings.


#include "EncGameState.h"

void AEncGameState::SetReadyState(bool bReady)
{
	bGameReady = bReady;
}

bool AEncGameState::IsReadyState() const
{
	return bGameReady;
}
