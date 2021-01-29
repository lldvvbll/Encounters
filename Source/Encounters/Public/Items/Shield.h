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

	float GetGaurdAngleCosine() const;

	void DrawGaurdAngle(FColor Color = FColor::Red) const;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Gaurd)
	float GaurdHalfAngle;

	UPROPERTY(VisibleInstanceOnly, Category = Gaurd)
	float GaurdAngleCosine = 0.0f;
};
