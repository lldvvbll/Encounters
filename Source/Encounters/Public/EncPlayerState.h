// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/PlayerState.h"
#include "EncPlayerState.generated.h"

class UEncCharacterStateComponent;
class UEncSaveGame;
struct FCharacterAbilityData;

UCLASS()
class ENCOUNTERS_API AEncPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AEncPlayerState();

	int32 GetLevel() const;
	void SetLevel(int32 NewLevel);

	int32 GetPoint() const;
	void SetPoint(int32 NewPoint);
	void ModifyPoint(int32 Amount);

	int32 GetStrength() const;
	void SetStrength(int32 NewStrength);

	int32 GetAgility() const;
	void SetAgility(int32 NewAgility);

	int32 GetVitality() const;
	void SetVitality(int32 NewVitality);

	int32 GetEndurance() const;
	void SetEndurance(int32 NewEndurance);

	void InitPlayerState();
	void LoadPlayerState(UEncSaveGame* SaveGame);

	void SetCharacterState(UEncCharacterStateComponent* NewState);

private:
	FCharacterAbilityData* FindCharacterAbilityData(int32 AbilityPoint) const;

protected:
	UPROPERTY(Transient)
	int32 Level;

	UPROPERTY(Transient)
	int32 Point;

	UPROPERTY(Transient)
	int32 Strength;

	UPROPERTY(Transient)
	int32 Agility;

	UPROPERTY(Transient)
	int32 Vitality;

	UPROPERTY(Transient)
	int32 Endurance;

	UPROPERTY(Transient)
	TWeakObjectPtr<UEncCharacterStateComponent> CharacterState;
};
