// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersGameMode.h"
#include "EncPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "EncPlayerState.h"

AEncountersGameMode::AEncountersGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AEncPlayerController::StaticClass();
	PlayerStateClass = AEncPlayerState::StaticClass();
}

void AEncountersGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AEncPlayerState* EncPlayerState = Cast<AEncPlayerState>(NewPlayer->PlayerState);
	return_if(EncPlayerState == nullptr);

	EncPlayerState->InitPlayerData();
}
