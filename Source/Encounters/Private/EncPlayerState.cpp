// Fill out your copyright notice in the Description page of Project Settings.


#include "EncPlayerState.h"
#include "EncGameInstance.h"
#include "DataStructures.h"
#include "Character/PlayerCharacter.h"
#include "Character/EncCharacterStateComponent.h"

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

	FCharacterAbilityData* Data = FindCharacterAbilityData(Strength);
	if (Data == nullptr)
		return;

}

int32 AEncPlayerState::GetAgility() const
{
	return Agility;
}

void AEncPlayerState::SetAgility(int32 NewAgility)
{
	Agility = NewAgility;

	FCharacterAbilityData* Data = FindCharacterAbilityData(Agility);
	if (Data == nullptr)
		return;

	CharacterState->SetRollingSpeed(Data->RollingSpeed);
	CharacterState->SetRollingVelocityRate(Data->RollingVelocityRate);
}

int32 AEncPlayerState::GetVitality() const
{
	return Vitality;
}

void AEncPlayerState::SetVitality(int32 NewVitality)
{
	Vitality = NewVitality;

	FCharacterAbilityData* Data = FindCharacterAbilityData(Strength);
	if (Data == nullptr)
		return;

	CharacterState->SetMaxHP(Data->HP);
	CharacterState->SetHP(Data->HP);
}

int32 AEncPlayerState::GetEndurance() const
{
	return Endurance;
}

void AEncPlayerState::SetEndurance(int32 NewEndurance)
{
	Endurance = NewEndurance;

	FCharacterAbilityData* Data = FindCharacterAbilityData(Strength);
	if (Data == nullptr)
		return;

	CharacterState->SetMaxStamina(Data->Stamina);
	CharacterState->SetStamina(Data->Stamina);
}

void AEncPlayerState::InitPlayerData()
{
	LOG_S(Warning);
	SetLevel(1);
	SetPoint(0);
	SetStrength(1);
	SetAgility(1);
	SetVitality(1);
	SetEndurance(1);
}

void AEncPlayerState::SetCharacterState(UEncCharacterStateComponent* NewState)
{
	if (NewState != nullptr)
	{
		CharacterState = NewState;
	}
	else
	{
		CharacterState.Reset();
	}
}

FCharacterAbilityData* AEncPlayerState::FindCharacterAbilityData(int32 AbilityPoint) const
{
	UEncGameInstance* EncGameInstance = Cast<UEncGameInstance>(GetGameInstance());
	return_if(EncGameInstance == nullptr, nullptr);
	
	return_if(!CharacterState.IsValid(), nullptr);

	return EncGameInstance->GetCharacterAbilityData(AbilityPoint);
}
