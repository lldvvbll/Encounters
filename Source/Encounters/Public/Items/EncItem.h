// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "EncItem.generated.h"

class UItemDataAsset;

UCLASS(Blueprintable)
class ENCOUNTERS_API UEncItem : public UObject
{
	GENERATED_BODY()

public:
	UEncItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UItemDataAsset* DataAsset;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Count;
};
