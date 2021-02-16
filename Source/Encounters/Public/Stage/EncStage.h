// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "UObject/NoExportTypes.h"
#include "EncStage.generated.h"

UCLASS(Blueprintable)
class ENCOUNTERS_API UEncStage : public UObject
{
	GENERATED_BODY()

public:
	void Init(const FPrimaryAssetId& NewDataAssetId);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FPrimaryAssetId DataAssetId;
};
