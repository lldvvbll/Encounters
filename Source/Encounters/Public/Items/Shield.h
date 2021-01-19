// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Equipment.h"
#include "Shield.generated.h"

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API AShield : public AEquipment
{
	GENERATED_BODY()
	
public:
	AShield();

	virtual void PostInitializeComponents() override;

	float GetGaurdAngleCosine() const;

	void DrawGaurdAngle() const;

private:
	UPROPERTY(EditDefaultsOnly, Category = Gaurd, Meta = (AllowPrivateAccess = true))
	float GaurdHalfAngle;

	float GaurdAngleCosine = 0.0f;
};
