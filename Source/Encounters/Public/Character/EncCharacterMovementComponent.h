// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EncCharacterMovementComponent.generated.h"

class AEncCharacter;

UCLASS()
class ENCOUNTERS_API UEncCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()	

public:
	virtual FVector ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity, const FVector& CurrentVelocity) const override;
};
