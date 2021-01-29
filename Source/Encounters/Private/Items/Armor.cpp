// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Armor.h"

AArmor::AArmor()
{
	StMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));

	RootComponent = StMeshComp;
	StMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}