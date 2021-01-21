// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Items/Equipment.h"
#include "Weapon.generated.h"

UCLASS()
class ENCOUNTERS_API AWeapon : public AEquipment
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetAttackBoxSocketPos() const;
	FVector GetAttackBoxHalfExtent() const;

	float GetAttackDamage() const;

	void DrawAttackBox(FColor Color = FColor::Red) const;

private:
	UPROPERTY(EditDefaultsOnly, Category = AttackTrace, Meta = (AllowPrivateAccess = true))
	FVector AttackBoxHalfExtent;

	UPROPERTY(EditAnywhere, Category = Damage, Meta = (AllowPrivateAccess = true))
	float DefaultDamage;
};
