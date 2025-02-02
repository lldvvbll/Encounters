// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Components/ActorComponent.h"
#include "EncStructures.h"
#include "InventoryComponent.generated.h"

class UEncItem;
class UEncSaveGame;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnAddItemDelegate, EPocketType, UEncItem*);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnRemoveItemDelegate, EPocketType, UEncItem*);

class FPocket
{
public:
	FPocket(EPocketType NewPocketType, int32 NewMaxCount);

	bool AddItem(UEncItem* NewItem);
	bool RemoveItem(UEncItem* Item);
	int32 GetItemCount() const;
	bool Contains(UEncItem* Item) const;
	EPocketType GetPocketType() const;

	template <typename ForEachFunc>
	void ForEachItem(ForEachFunc Func)
	{
		for (auto& Item : ItemSet)
		{
			Func(Item);
		}
	}

private:
	EPocketType PocketType;
	int32 MaxCount;
	TSet<UEncItem*> ItemSet;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENCOUNTERS_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInventoryComponent();

	void AddItem(UEncItem* Item, EPocketType PocketType = EPocketType::Default);
	void AddItemFromSaveItemData(const FSaveItemData& SaveItemData);
	void AddItemFromSaveItemDatas(const TArray<FSaveItemData>& SaveItemDatas);
	void RemoveItemInPocket(UEncItem* Item, EPocketType PocketType);
	void RemoveItem(UEncItem* Item);
	int32 GetItemCount(EPocketType PocketType) const;
	int32 GetItemCountAll() const;

	void LoadInventory(const UEncSaveGame* SaveGame);
	void SaveInventory(UEncSaveGame* SaveGame);

public:
	FOnAddItemDelegate OnAddItem;
	FOnRemoveItemDelegate OnRemoveItem;

private:
	TMap<EPocketType, FPocket> PocketMap;
};
