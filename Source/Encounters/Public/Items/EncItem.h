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
	void Init(const FPrimaryAssetId& NewDataAssetId, int32 NewCount);

	const FPrimaryAssetId& GetId() const;
	UItemDataAsset* GetDataAsset() const;
	int32 GetCount() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId DataAssetId;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Count;
};
