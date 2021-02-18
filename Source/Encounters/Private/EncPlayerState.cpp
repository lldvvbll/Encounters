// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerState.h"
#include "Character/PlayerCharacter.h"
#include "EncSaveGame.h"
#include "EncStructures.h"
#include "EncGameInstance.h"

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
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Level);
}

int32 AEncPlayerState::GetPoint() const
{
	return Point;
}

void AEncPlayerState::SetPoint(int32 NewPoint)
{
	Point = NewPoint;
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Point);
}

void AEncPlayerState::ModifyPoint(int32 Amount)
{
	SetPoint(FMath::Max(Point + Amount, 0));
}

int32 AEncPlayerState::GetStrength() const
{
	return Strength;
}

void AEncPlayerState::SetStrength(int32 NewStrength)
{
	Strength = NewStrength;
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Strength);
}

int32 AEncPlayerState::GetAgility() const
{
	return Agility;
}

void AEncPlayerState::SetAgility(int32 NewAgility)
{
	Agility = NewAgility;
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Agility);
}

int32 AEncPlayerState::GetVitality() const
{
	return Vitality;
}

void AEncPlayerState::SetVitality(int32 NewVitality)
{
	Vitality = NewVitality;
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Vitality);
}

int32 AEncPlayerState::GetEndurance() const
{
	return Endurance;
}

void AEncPlayerState::SetEndurance(int32 NewEndurance)
{
	Endurance = NewEndurance;
	OnPlayerStateChanged.Broadcast(EPlayerStateAttribute::Endurance);
}

void AEncPlayerState::InitPlayerState()
{
	UEncGameInstance* EncGameInstance = GetGameInstance<UEncGameInstance>();
	return_if(EncGameInstance == nullptr);

	const FSavePlayerStateData& DefaultState = EncGameInstance->GetDefaultPlayerState();

	SetLevel(DefaultState.Level);
	SetPoint(DefaultState.Point);
	SetStrength(DefaultState.Strength);
	SetAgility(DefaultState.Agility);
	SetVitality(DefaultState.Vitality);
	SetEndurance(DefaultState.Endurance);
}

void AEncPlayerState::LoadPlayerState(const UEncSaveGame* SaveGame)
{
	return_if(SaveGame == nullptr);

	const FSavePlayerStateData& PlayerState = SaveGame->PlayerState;

	SetLevel(PlayerState.Level);
	SetPoint(PlayerState.Point);
	SetStrength(PlayerState.Strength);
	SetAgility(PlayerState.Agility);
	SetVitality(PlayerState.Vitality);
	SetEndurance(PlayerState.Endurance);
}

void AEncPlayerState::SavePlayerState(UEncSaveGame* SaveGame)
{
	return_if(SaveGame == nullptr);

	FSavePlayerStateData& PlayerState = SaveGame->PlayerState;

	PlayerState.Level = Level;
	PlayerState.Point = Point;
	PlayerState.Strength = Strength;
	PlayerState.Agility = Agility;
	PlayerState.Vitality = Vitality;
	PlayerState.Endurance = Endurance;
}
