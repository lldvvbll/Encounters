// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Shield.generated.h"

UCLASS()
class ENCOUNTERS_API AShield : public AEquipment
{
	GENERATED_BODY()
	
public:
	AShield();

	float GetGuardAngleCosine() const;
	float GetUseStaminaOnGuard() const;
	float GetDamageReduction() const;

	void DrawGuardAngle(FColor Color = FColor::Red) const;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Guard)
	float GuardHalfAngle;

	UPROPERTY(VisibleInstanceOnly, Category = Guard)
	float GuardAngleCosine;
};
