// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "EncStructures.generated.h"

UENUM(BlueprintType)
enum class EPocketType : uint8
{
	Default,
	Weapon,
	Shield,
	Armor,
};
