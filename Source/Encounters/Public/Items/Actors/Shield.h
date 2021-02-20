// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Shield.generated.h"

class UItemDataAsset;
class UShieldDataAsset;

UCLASS()
class ENCOUNTERS_API AShield : public AEquipment
{
	GENERATED_BODY()
	
public:
	AShield();

	virtual void SetItemDataAsset(UItemDataAsset* DataAsset) override;
	const UShieldDataAsset* GetShieldDataAsset() const;

	float GetGuardAngleCosine() const;
	float GetUseStaminaOnGuard() const;
	float GetDamageReduction() const;
	float GetGuardSpeed() const;

	void DrawDebugGuardAngle(FColor Color = FColor::Red) const;

protected:
	UPROPERTY()
	UShieldDataAsset* ShieldDataAsset;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Guard)
	float GuardHalfAngle;

	UPROPERTY(VisibleInstanceOnly, Category = Guard)
	float GuardAngleCosine;
};
