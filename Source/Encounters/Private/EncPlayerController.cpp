// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerController.h"
#include "UI/HudWidget.h"
#include "Character/PlayerCharacter.h"
#include "Character/EncCharacterStateComponent.h"
#include "EncSaveGame.h"
#include "EncPlayerState.h"
#include "EncGameInstance.h"

AEncPlayerController::AEncPlayerController()
{
	static ConstructorHelpers::FClassFinder<UHudWidget> UI_HUD(
		TEXT("/Game/Encounters/UI/UI_HUD.UI_HUD_C"));
	if (UI_HUD.Succeeded())
	{
		HudWidgetClass = UI_HUD.Class;
	}
}

void AEncPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	ACharacter* Char = GetCharacter();
	PlayerCharacter = (Char != nullptr) ? Cast<APlayerCharacter>(Char) : nullptr;
}

bool AEncPlayerController::LoadOrCreateSaveGame()
{
	static FString SlotName = TEXT("Default");
	static int32 UserIndex = 0;

	if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		CurrentSaveGame = Cast<UEncSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));

		AEncPlayerState* EncPlayerState = GetPlayerState<AEncPlayerState>();
		if (EncPlayerState != nullptr)
		{
			EncPlayerState->LoadPlayerState(CurrentSaveGame);
		}

		PlayerCharacter->LoadCharacter(CurrentSaveGame);
	}
	else
	{
		CurrentSaveGame = Cast<UEncSaveGame>(UGameplayStatics::CreateSaveGameObject(UEncSaveGame::StaticClass()));

		AEncPlayerState* EncPlayerState = GetPlayerState<AEncPlayerState>();
		if (EncPlayerState != nullptr)
		{
			EncPlayerState->InitPlayerState();
		}

		PlayerCharacter->InitCharacterData();
	}

	return false;
}

void AEncPlayerController::BeginPlay()
{
	Super::BeginPlay();

	HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
	HudWidget->AddToViewport();

	if (PlayerCharacter != nullptr)
	{
		HudWidget->BindCharacterState(PlayerCharacter->GetCharacterStateComponent());
	}
}
