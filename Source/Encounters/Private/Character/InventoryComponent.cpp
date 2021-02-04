// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/InventoryComponent.h"
#include "Items/EncItem.h"

FPocket::FPocket(EPocketType NewPocketType, int32 NewMaxCount)
{
	PocketType = NewPocketType;
	MaxCount = NewMaxCount;
}

void FPocket::AddItem(UEncItem* NewItem)
{
	if (MaxCount > 0 && GetItemCount() >= MaxCount)
		return;

	ItemSet.Emplace(NewItem);
}

void FPocket::RemoveItem(UEncItem* Item)
{
	ItemSet.Remove(Item);
}

int32 FPocket::GetItemCount() const
{
	return ItemSet.Num();
}

bool FPocket::Contains(UEncItem* Item) const
{
	return ItemSet.Contains(Item);
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

	Pocket->AddItem(Item);

	OnAddItem.Broadcast(PocketType, Item);
}

void UInventoryComponent::RemoveItemInPocket(UEncItem* Item, EPocketType PocketType)
{
	return_if(Item == nullptr);

	FPocket* Pocket = PocketMap.Find(PocketType);
	if (Pocket == nullptr)
		return;

	Pocket->RemoveItem(Item);

	OnRemoveItem.Broadcast(PocketType, Item);
}

void UInventoryComponent::RemoveItem(UEncItem* Item)
{
	for (auto& PocketPair : PocketMap)
	{
		FPocket& Pocket = PocketPair.Value;
		if (Pocket.Contains(Item))
		{
			Pocket.RemoveItem(Item);
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

void UInventoryComponent::LoadInventory(UEncSaveGame* SaveGame)
{
	return_if(SaveGame == nullptr);


}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();


}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();


}
