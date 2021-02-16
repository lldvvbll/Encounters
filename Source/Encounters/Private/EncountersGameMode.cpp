// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersGameMode.h"
#include "EncPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "Character/NpcCharacter.h"
#include "EncPlayerState.h"
#include "EncPlayerController.h"
#include "EncAssetManager.h"
#include "Character/DataAssets/NpcDataAsset.h"
#include "Stage/SpawnBox.h"
#include "EngineUtils.h"

AEncountersGameMode::AEncountersGameMode()
{
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AEncPlayerController::StaticClass();
	PlayerStateClass = AEncPlayerState::StaticClass();
}

void AEncountersGameMode::StartPlay()
{
	Super::StartPlay();

	for (TActorIterator<ASpawnBox> It(GetWorld()); It; ++It)
	{
		SpawnBoxes.Emplace(*It);
	}
}

void AEncountersGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AEncPlayerController* EncPlayerController = Cast<AEncPlayerController>(NewPlayer);
	return_if(EncPlayerController == nullptr);

	EncPlayerController->LoadOrCreateSaveGame();
}

void AEncountersGameMode::SpawnEnemy() const
{
	static FString DataAssetTypeAndName = TEXT("Enemy:KnightDataAsset");

	UWorld* World = GetWorld();
	return_if(World == nullptr);

	APlayerController* PlayerController = World->GetFirstPlayerController();
	return_if(PlayerController == nullptr);

	auto Pawn = PlayerController->GetPawn();
	return_if(Pawn == nullptr);

	auto DataAsset = UEncAssetManager::Get().GetDataAsset<UNpcDataAsset>(FPrimaryAssetId(DataAssetTypeAndName));
	return_if(DataAsset == nullptr);

	FVector Pos = Pawn->GetActorLocation() + Pawn->GetActorForwardVector() * 1000.0f;
		
	World->SpawnActor<ANpcCharacter>(DataAsset->NpcActorClass, Pos, FRotator::ZeroRotator);
}
