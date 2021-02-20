// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Weapon.generated.h"

class UItemDataAsset;
class UWeaponDataAsset;

UCLASS()
class ENCOUNTERS_API AWeapon : public AEquipment
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	virtual void SetItemDataAsset(UItemDataAsset* DataAsset) override;
	const UWeaponDataAsset* GetWeaponDataAsset() const;

	float GetAttackDamage() const;
	float GetAttackSpeed() const;
	FVector GetCollisionBoxPos() const;
	FCollisionShape GetCollisionBox() const;

	float GetUseStaminaOnAttack() const;

	void DrawDebugCollisionBox(FColor Color = FColor::Red) const;

protected:
	UPROPERTY()
	UWeaponDataAsset* WeaponDataAsset;

	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionBox;
};
