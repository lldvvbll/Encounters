// Fill out your copyright notice in the Description page of Project Settings.


#include "EncountersGameMode.h"
#include "EncPlayerController.h"
#include "Character/PlayerCharacter.h"
#include "Character/NpcCharacter.h"
#include "EncPlayerState.h"
#include "EncPlayerController.h"
#include "EncAssetManager.h"
#include "Character/DataAssets/NpcDataAsset.h"
#include "Stage/DataAssets/StageDataAsset.h"
#include "Stage/SpawnBox.h"
#include "Stage/EncStage.h"
#include "EngineUtils.h"
#include "EncGameInstance.h"

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

	auto GameInstance = GetGameInstance<UEncGameInstance>();
	return_if(GameInstance == nullptr);

	FPrimaryAssetId StageDataAssetId = GameInstance->GetCurrentStageDataAssetId();
	return_if(!StageDataAssetId.IsValid());

	StageDataAsset = UEncAssetManager::Get().GetDataAsset<UStageDataAsset>(StageDataAssetId);
	return_if(StageDataAsset == nullptr);

	StartStage();
}

void AEncountersGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	AEncPlayerController* EncPlayerController = Cast<AEncPlayerController>(NewPlayer);
	return_if(EncPlayerController == nullptr);

	EncPlayerController->LoadOrCreateSaveGame();
}

void AEncountersGameMode::exec_SpawnEnemy() const
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

void AEncountersGameMode::StartStage()
{
	SpawnEnemies();


}

void AEncountersGameMode::SpawnEnemies()
{
	return_if(SpawnBoxes.Num() == 0);

	for (auto& Pair : StageDataAsset->EnemyMap)
	{
		FPrimaryAssetId& EnemyDataAssetId = Pair.Key;
		int32& Count = Pair.Value;

		UNpcDataAsset* NpcDataAsset = UEncAssetManager::Get().GetDataAsset<UNpcDataAsset>(EnemyDataAssetId);
		if (NpcDataAsset == nullptr)
			continue;

		for (int32 i = 0; i < Count; ++i)
		{
			FVector Pos = SpawnBoxes[FMath::RandRange(0, SpawnBoxes.Num() - 1)]->GetActorLocation();
			FRotator Rot(0.0f, FMath::FRandRange(-180.f, 180.f), 0.0f);

			auto Enemy = GetWorld()->SpawnActor<ANpcCharacter>(NpcDataAsset->NpcActorClass, Pos, Rot);
			Enemy->OnNpcDead.AddUObject(this, &AEncountersGameMode::OnEnemyDead);

			Enemies.Emplace(Enemy);
		}
	}
}

void AEncountersGameMode::OnEnemyDead(ANpcCharacter* DeadEnemy)
{
	int32 RemovedEnemyCount = Enemies.Remove(DeadEnemy);
	if (RemovedEnemyCount != 1)
	{
		LOG(Warning, TEXT("Failed To Remove Enemy"));
	}

	if (Enemies.Num() <= 0)
	{
	}
}
