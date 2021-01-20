// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NpcCharacter.h"
#include "EncAIController.h"

ANpcCharacter::ANpcCharacter()
{
	AIControllerClass = AEncAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}