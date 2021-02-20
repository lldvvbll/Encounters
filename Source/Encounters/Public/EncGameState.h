// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/GameStateBase.h"
#include "EncGameState.generated.h"

UCLASS()
class ENCOUNTERS_API AEncGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	void SetDrawDebugDetectRange(bool bDraw);
	bool IsDrawDebugDetectRange() const;

	void SetDrawDebugWeaponCollisionBox(bool bDraw);
	bool IsDrawDebugWeaponCollisionBox() const;

	void SetDrawDebugGuard(bool bDraw);
	bool IsDrawDebugGuard() const;

	void SetDrawDebugAvoid(bool bDraw);
	bool IsDrawDebugAvoid() const;

private:
	UPROPERTY(Transient)
	bool bDrawDebugDetectRange;

	UPROPERTY(Transient)
	bool bDrawDebugWeaponCollisionBox;

	UPROPERTY(Transient)
	bool bDrawDebugGuard;

	UPROPERTY(Transient)
	bool bDrawDebugAvoid;
};
