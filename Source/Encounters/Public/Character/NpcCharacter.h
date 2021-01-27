// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Character/EncCharacter.h"
#include "NpcCharacter.generated.h"

UCLASS()
class ENCOUNTERS_API ANpcCharacter : public AEncCharacter
{
	GENERATED_BODY()
	
public:
	ANpcCharacter();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Dead() override;

private:
	UPROPERTY(VisibleAnywhere, Category = UI, Meta = (AllowPrivateAccess = true))
	UWidgetComponent* HpBarWidget;
};
