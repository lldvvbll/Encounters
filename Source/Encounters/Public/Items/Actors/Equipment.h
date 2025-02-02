// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

class UItemDataAsset;

UCLASS(Abstract)
class ENCOUNTERS_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:
	AEquipment();

	virtual void SetItemDataAsset(UItemDataAsset* DataAsset);
	const UItemDataAsset* GetItemDataAsset() const;

	FVector GetAttachOffset() const;
	FRotator GetAttachRotator() const;

protected:
	UPROPERTY()
	UItemDataAsset* ItemDataAsset;

	UPROPERTY(EditDefaultsOnly, Category = Transform)
	FVector AttachOffset;

	UPROPERTY(EditDefaultsOnly, Category = Transform)
	FRotator AttachRotator;
};
