// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InventoryComponent.h"
#include "Items/EncItem.h"
#include "EncSaveGame.h"

FPocket::FPocket(EPocketType NewPocketType, int32 NewMaxCount)
{
	PocketType = NewPocketType;
	MaxCount = NewMaxCount;
}

bool FPocket::AddItem(UEncItem* NewItem)
{
	if (MaxCount > 0 && GetItemCount() >= MaxCount)
		return false;

	return ItemSet.Emplace(NewItem).IsValidId();
}

bool FPocket::RemoveItem(UEncItem* Item)
{
	return (ItemSet.Remove(Item) > 0);
}

int32 FPocket::GetItemCount() const
{
	return ItemSet.Num();
}

bool FPocket::Contains(UEncItem* Item) const
{
	return ItemSet.Contains(Item);
}

EPocketType FPocket::GetPocketType() const
{
	return PocketType;
}

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	PocketMap.Emplace(EPocketType::Default, FPocket(EPocketType::Default, 0));	// 무제한 포켓
	PocketMap.Emplace(EPocketType::Weapon, FPocket(EPocketType::Weapon, 1));
	PocketMap.Emplace(EPocketType::Shield, FPocket(EPocketType::Shield, 1));
	PocketMap.Emplace(EPocketType::Armor, FPocket(EPocketType::Armor, 1));
}

void UInventoryComponent::AddItem(UEncItem* Item, EPocketType PocketType/* = EPocketType::Default*/)
{
	return_if(Item == nullptr);

	FPocket* Pocket = PocketMap.Find(PocketType);
	if (Pocket == nullptr)
		return;

	if (Pocket->AddItem(Item))
	{
		OnAddItem.Broadcast(PocketType, Item);
	}	
}

void UInventoryComponent::AddItemFromSaveItemData(const FSaveItemData& SaveItemData)
{
	UEncItem* NewItem = NewObject<UEncItem>(this);
	if (NewItem == nullptr)
	{
		LOG(Warning, TEXT("Fail to Add Item. %s"), *(SaveItemData.AssetId.ToString()));
		return;
	}
	NewItem->Init(SaveItemData.AssetId, SaveItemData.Count);

	AddItem(NewItem, SaveItemData.PocketType);
}

void UInventoryComponent::AddItemFromSaveItemDatas(const TArray<FSaveItemData>& SaveItemDatas)
{
	for (auto& ItemData : SaveItemDatas)
	{
		AddItemFromSaveItemData(ItemData);
	}
}

void UInventoryComponent::RemoveItemInPocket(UEncItem* Item, EPocketType PocketType)
{
	return_if(Item == nullptr);

	FPocket* Pocket = PocketMap.Find(PocketType);
	if (Pocket == nullptr)
		return;

	if (Pocket->RemoveItem(Item))
	{
		OnRemoveItem.Broadcast(PocketType, Item);
	}	
}

void UInventoryComponent::RemoveItem(UEncItem* Item)
{
	for (auto& PocketPair : PocketMap)
	{
		FPocket& Pocket = PocketPair.Value;
		if (Pocket.Contains(Item))
		{
			if (Pocket.RemoveItem(Item))
			{
				OnRemoveItem.Broadcast(Pocket.GetPocketType(), Item);
			}			
			break;
		}
	}
}

int32 UInventoryComponent::GetItemCount(EPocketType PocketType) const
{
	const FPocket* Pocket = PocketMap.Find(PocketType);
	if (Pocket == nullptr)
		return 0;

	return Pocket->GetItemCount();
}

int32 UInventoryComponent::GetItemCountAll() const
{
	int32 Count = 0;
	for (auto& PocketPair : PocketMap)
	{
		Count += (PocketPair.Value).GetItemCount();
	}

	return Count;
}

void UInventoryComponent::LoadInventory(const UEncSaveGame* SaveGame)
{
	return_if(SaveGame == nullptr);

	AddItemFromSaveItemDatas(SaveGame->Items);
}

void UInventoryComponent::SaveInventory(UEncSaveGame* SaveGame)
{
	return_if(SaveGame == nullptr);

	for (auto& PocketPair : PocketMap)
	{
		FPocket& Pocket = PocketPair.Value;
		Pocket.ForEachItem(
			[&SaveGame, &Pocket](UEncItem* Item)
			{
				return_if(Item == nullptr);

				SaveGame->Items.Emplace(Item->GetDataAssetId(), Pocket.GetPocketType(), Item->GetCount());
			});
	}
}
