// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Actor.h"
#include "SpawnBox.generated.h"

UCLASS()
class ENCOUNTERS_API ASpawnBox : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnBox();

private:
	UPROPERTY(VisibleAnywhere, Category = Box, Meta = (AllowPrivateAccess = true))
	UBoxComponent* Box;
};
