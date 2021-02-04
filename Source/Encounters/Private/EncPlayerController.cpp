// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerController.h"
#include "UI/HudWidget.h"
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

		SaveGame();
	}

	return false;
}

void AEncPlayerController::SaveGame()
{
	static FString SlotName = TEXT("Default");
	static int32 UserIndex = 0;

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

void AEncPlayerController::BindCharacterIneventory(UInventoryComponent* Inventory)
{
	return_if(Inventory == nullptr);

	OnAddItemDelegateHandle = Inventory->OnAddItem.AddUObject(this, &AEncPlayerController::OnItemAdded);
	OnRemoveItemDelegateHandle = Inventory->OnRemoveItem.AddUObject(this, &AEncPlayerController::OnItemRemoved);
}

void AEncPlayerController::UnbindCharacterInventory(UInventoryComponent* Inventory)
{
	return_if(Inventory == nullptr);
	
	Inventory->OnAddItem.Remove(OnAddItemDelegateHandle);
	Inventory->OnRemoveItem.Remove(OnRemoveItemDelegateHandle);
}

void AEncPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);

	if (auto EncPlayerState = Cast<AEncPlayerState>(PlayerState))
	{
		OnPlayerStateChangedDelegateHandle = 
			EncPlayerState->OnPlayerStateChanged.AddUObject(this, &AEncPlayerController::OnPlayerStateChanged);
	}
}

void AEncPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	if (auto EncPlayerState = Cast<AEncPlayerState>(PlayerState))
	{
		EncPlayerState->OnPlayerStateChanged.Remove(OnPlayerStateChangedDelegateHandle);
	}
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

void AEncPlayerController::OnItemAdded(EPocketType PocketType, UEncItem* ChangedItem)
{
	SaveGame();
}

void AEncPlayerController::OnItemRemoved(EPocketType PocketType, UEncItem* RemovedItem)
{
	SaveGame();
}

void AEncPlayerController::OnPlayerStateChanged(EPlayerStateAttribute Attribute)
{
	SaveGame();
}
