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

	void BindCharacterIneventory(UInventoryComponent* Inventory);
	void UnbindCharacterInventory(UInventoryComponent* Inventory);

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;
	virtual void BeginPlay() override;

	void OnItemAdded(EPocketType PocketType, UEncItem* AddedItem);
	void OnItemRemoved(EPocketType PocketType, UEncItem* RemovedItem);
	void OnPlayerStateChanged(EPlayerStateAttribute Attribute);

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
};
