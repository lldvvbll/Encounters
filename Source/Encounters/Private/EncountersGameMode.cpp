// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersGameMode.h"
#include "EncPlayerController.h"
#include "Character/EncCharacter.h"

AEncountersGameMode::AEncountersGameMode()
{
	DefaultPawnClass = AEncCharacter::StaticClass();
	PlayerControllerClass = AEncPlayerController::StaticClass();
}