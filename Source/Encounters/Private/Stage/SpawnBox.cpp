// Fill out your copyright notice in the Description page of Project Settings.


#include "Stage/SpawnBox.h"
#include "EncountersGameMode.h"

ASpawnBox::ASpawnBox()
{
	PrimaryActorTick.bCanEverTick = false;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));

	RootComponent = Box;

	Box->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
}
