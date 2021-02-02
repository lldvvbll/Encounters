// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Armor.generated.h"

UCLASS()
class ENCOUNTERS_API AArmor : public AEquipment
{
	GENERATED_BODY()
	
public:
	AArmor();

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	UStaticMeshComponent* StMeshComp;
};
