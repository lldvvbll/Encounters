// Fill out your copyright notice in the Description page of Project Settings.


#include "EncGameState.h"

void AEncGameState::SetDrawDebugDetectRange(bool bDraw)
{
	bDrawDebugDetectRange = bDraw;
}

bool AEncGameState::IsDrawDebugDetectRange() const
{
	return bDrawDebugDetectRange;
}

void AEncGameState::SetDrawDebugWeaponCollisionBox(bool bDraw)
{
	bDrawDebugWeaponCollisionBox = bDraw;
}

bool AEncGameState::IsDrawDebugWeaponCollisionBox() const
{
	return bDrawDebugWeaponCollisionBox;
}

void AEncGameState::SetDrawDebugGuard(bool bDraw)
{
	bDrawDebugGuard = bDraw;
}

bool AEncGameState::IsDrawDebugGuard() const
{
	return bDrawDebugGuard;
}

void AEncGameState::SetDrawDebugAvoid(bool bDraw)
{
	bDrawDebugAvoid = bDraw;
}

bool AEncGameState::IsDrawDebugAvoid() const
{
	return bDrawDebugAvoid;
}
