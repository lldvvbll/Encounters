// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Actors/Equipment.h"
#include "Weapon.generated.h"

UCLASS()
class ENCOUNTERS_API AWeapon : public AEquipment
{
	GENERATED_BODY()
	
public:	
	AWeapon();

	float GetAttackDamage() const;
	FVector GetCollisionBoxPos() const;
	FCollisionShape GetCollisionBox() const;

	float GetUseStaminaOnAttack() const;

	void DrawAttackBox(FColor Color = FColor::Red) const;

protected:
	UPROPERTY(VisibleAnywhere, Category = Mesh)
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Collision)
	UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = Damage)
	float DefaultDamage;
};
