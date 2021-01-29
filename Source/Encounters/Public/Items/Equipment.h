// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Actor.h"
#include "Equipment.generated.h"

UCLASS()
class ENCOUNTERS_API AEquipment : public AActor
{
	GENERATED_BODY()
	
public:
	AEquipment();

	FVector GetAttachOffset() const;
	FRotator GetAttachRotator() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = Transform)
	FVector AttachOffset;

	UPROPERTY(EditDefaultsOnly, Category = Transform)
	FRotator AttachRotator;
};
