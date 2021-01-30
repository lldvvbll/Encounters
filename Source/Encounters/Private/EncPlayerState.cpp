// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerState.h"
#include "Character/PlayerCharacter.h"

AEncPlayerState::AEncPlayerState()
{
	Level = 1;
	Point = 0;
	Strength = 1;
	Agility = 1;
	Vitality = 1;
	Endurance = 1;
}

int32 AEncPlayerState::GetLevel() const
{
	return Level;
}

void AEncPlayerState::SetLevel(int32 NewLevel)
{
	Level = NewLevel;
}

int32 AEncPlayerState::GetPoint() const
{
	return Point;
}

void AEncPlayerState::SetPoint(int32 NewPoint)
{
	Point = NewPoint;
}

void AEncPlayerState::ModifyPoint(int32 Amount)
{
	Point = FMath::Max(Point + Amount, 0);
}

int32 AEncPlayerState::GetStrength() const
{
	return Strength;
}

void AEncPlayerState::SetStrength(int32 NewStrength)
{
	Strength = NewStrength;
	
}

int32 AEncPlayerState::GetAgility() const
{
	return Agility;
}

void AEncPlayerState::SetAgility(int32 NewAgility)
{
	Agility = NewAgility;
}

int32 AEncPlayerState::GetVitality() const
{
	return Vitality;
}

void AEncPlayerState::SetVitality(int32 NewVitality)
{
	Vitality = NewVitality;
}

int32 AEncPlayerState::GetEndurance() const
{
	return Endurance;
}

void AEncPlayerState::SetEndurance(int32 NewEndurance)
{
	Endurance = NewEndurance;
}

void AEncPlayerState::InitPlayerData()
{
	SetLevel(1);
	SetPoint(0);
	SetStrength(1);
	SetAgility(1);
	SetVitality(1);
	SetEndurance(1);
}
