// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/PlayerController.h"
#include "EncStructures.h"
#include "EncPlayerController.generated.h"

class UHudWidget;
class APlayerCharacter;
class UEncSaveGame;
class UInventoryComponent;
class UEncItem;

UCLASS()
class ENCOUNTERS_API AEncPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AEncPlayerController();

	virtual void SetPawn(APawn* InPawn) override;

	bool LoadOrCreateSaveGame();
	void SaveGame();

	void ChangeInputMode(bool bGameMode);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

	UPROPERTY()
	UEncSaveGame* CurrentSaveGame;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UHudWidget> HudWidgetClass;

	UPROPERTY()
	UHudWidget* HudWidget;

	FDelegateHandle OnAddItemDelegateHandle;
	FDelegateHandle OnRemoveItemDelegateHandle;
	FDelegateHandle OnPlayerStateChangedDelegateHandle;

	FInputModeGameOnly GameInputMode;
	FInputModeUIOnly UiInputMode;
};
