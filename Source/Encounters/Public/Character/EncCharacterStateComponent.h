// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Components/ActorComponent.h"
#include "EncCharacterStateComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHpChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENCOUNTERS_API UEncCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEncCharacterStateComponent();

public:
	void SetDamage(float NewDamage);
	void SetHP(float NewHP);
	float GetHpRatio() const;

protected:
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;

public:
	FOnHpIsZeroDelegate OnHpIsZero;
	FOnHpChangedDelegate OnHpChanged;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	float MAX_HP = 100.0f;
};
