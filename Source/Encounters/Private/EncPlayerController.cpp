// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerController.h"
#include "UI/HudWidget.h"
#include "UI/PlayerStateWidget.h"
#include "Character/PlayerCharacter.h"
#include "Character/EncCharacterStateComponent.h"
#include "Character/InventoryComponent.h"
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

	static ConstructorHelpers::FClassFinder<UPlayerStateWidget> UI_PLAYERSTATE(
		TEXT("/Game/Encounters/UI/UI_PlayerState.UI_PlayerState_C"));
	if (UI_PLAYERSTATE.Succeeded())
	{
		PlayerStateWidgetClass = UI_PLAYERSTATE.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_STAGECLEAR(
		TEXT("/Game/Encounters/UI/UI_StageClear.UI_StageClear_C"));
	if (UI_STAGECLEAR.Succeeded())
	{
		StageClearWidgetClass = UI_STAGECLEAR.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ALLSTAGECLEAR(
		TEXT("/Game/Encounters/UI/UI_AllStageClear.UI_AllStageClear_C"));
	if (UI_ALLSTAGECLEAR.Succeeded())
	{
		AllStageClearWidgetClass = UI_ALLSTAGECLEAR.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_YOUDIED(
		TEXT("/Game/Encounters/UI/UI_YouDied.UI_YouDied_C"));
	if (UI_YOUDIED.Succeeded())
	{
		YouDiedWidgetClass = UI_YOUDIED.Class;
	}
}

void AEncPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	PlayerCharacter = Cast<APlayerCharacter>(InPawn);
	return_if(PlayerCharacter == nullptr);

	PlayerCharacter->OnPlayerDead.AddUObject(this, &AEncPlayerController::OnPlayerDead);
}

bool AEncPlayerController::LoadOrCreateSaveGame()
{
	const FString& SlotName = UEncGameInstance::SaveGameSlotName;
	const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;

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

		SaveGame();
	}

	return false;
}

void AEncPlayerController::SaveGame()
{
	const FString& SlotName = UEncGameInstance::SaveGameSlotName;
	const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;

	UEncSaveGame* NewSaveGame = NewObject<UEncSaveGame>();
	return_if(NewSaveGame == nullptr);

	AEncPlayerState* EncPlayerState = GetPlayerState<AEncPlayerState>();
	if (EncPlayerState != nullptr)
	{
		EncPlayerState->SavePlayerState(NewSaveGame);
	}

	PlayerCharacter->SaveCharacter(NewSaveGame);

	if (!UGameplayStatics::SaveGameToSlot(NewSaveGame, SlotName, UserIndex))
	{
		LOG(Error, TEXT("SaveGame Error"));
	}
}

void AEncPlayerController::ChangeInputMode(bool bGameMode)
{
	if (bGameMode)
	{
		SetInputMode(GameInputMode);
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(UiInputMode);
		bShowMouseCursor = true;
	}
}

APlayerCharacter* AEncPlayerController::GetPlayerCharacter() const
{
	return PlayerCharacter;
}

void AEncPlayerController::OnPlayerDead()
{
	SaveGame();

	if (auto YouDiedWidget = CreateWidget<UUserWidget>(this, YouDiedWidgetClass))
	{
		YouDiedWidget->AddToViewport(1);
	}

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, 
		FTimerDelegate::CreateLambda(
			[this]()
			{
				UGameplayStatics::OpenLevel(GetWorld(), TEXT("PlayerState"));
			}), 
		3.0f, false);
}

void AEncPlayerController::OnStageCleard(bool bAllClear)
{
	TSubclassOf<UUserWidget>& ClearWidgetClass = bAllClear ? AllStageClearWidgetClass : StageClearWidgetClass;
	if (auto ClearWidget = CreateWidget<UUserWidget>(this, ClearWidgetClass))
	{
		ClearWidget->AddToViewport(1);
	}

	if (bAllClear)
	{
		const FString& SlotName = UEncGameInstance::SaveGameSlotName;
		const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;
		if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
		{
			UGameplayStatics::DeleteGameInSlot(SlotName, UserIndex);
		}
	}	
}

void AEncPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ChangeInputMode(true);

	HudWidget = CreateWidget<UHudWidget>(this, HudWidgetClass);
	HudWidget->AddToViewport();

	if (PlayerCharacter != nullptr)
	{
		HudWidget->BindCharacterState(PlayerCharacter->GetCharacterStateComponent());
	}
}

void AEncPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("GamePause"), EInputEvent::IE_Pressed, this, &AEncPlayerController::OnGamePause);
}

void AEncPlayerController::OnGamePause()
{
	PlayerStateWidget = CreateWidget<UPlayerStateWidget>(this, PlayerStateWidgetClass);
	return_if(PlayerStateWidget == nullptr);

	PlayerStateWidget->Bind(true);
	PlayerStateWidget->AddToViewport(3);

	SetPause(true);
	ChangeInputMode(false);
}