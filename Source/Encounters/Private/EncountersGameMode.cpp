// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersGameMode.h"
#include "EncPlayerController.h"
#include "Character/PlayerCharacter.h"

AEncountersGameMode::AEncountersGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AEncPlayerController::StaticClass();
}