// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Components/ActorComponent.h"
#include "EncCharacterStateComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnHpIsZeroDelegate);
DECLARE_MULTICAST_DELEGATE(FOnHpChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnStaminaChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMaxHpChangedDelegate);
DECLARE_MULTICAST_DELEGATE(FOnMaxStaminaChangedDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENCOUNTERS_API UEncCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UEncCharacterStateComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetAttackPower(float NewAttackPower);
	float GetAttackPower() const;

	void SetHP(float NewHP);
	void ModifyHP(float Amount);
	float GetHP() const;
	void SetMaxHP(float NewHP);
	float GetMaxHP() const;
	float GetHpRatio() const;

	void SetStamina(float NewStamina);
	void ModifyStamina(float Amount);
	float GetStamina() const;
	void SetMaxStamina(float NewStamina);
	float GetMaxStamina() const;
	float GetStaminaRatio() const;

	void SetRollingSpeed(float NewRollingSpeed);
	float GetRolligSpeed() const;
	void SetRollingVelocityRate(float NewRate);
	float GetRollingVelocityRate() const;

protected:
	virtual void BeginPlay() override;

public:
	FOnHpIsZeroDelegate OnHpIsZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStaminaChangedDelegate OnStaminaChanged;
	FOnMaxHpChangedDelegate OnMaxHpChanged;
	FOnMaxStaminaChangedDelegate OnMaxStaminaChanged;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float AttackPower;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float CurrentStamina;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float MaxHP;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float HpRecoverySpeed;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float MaxStamina;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float StaminaRecoverySpeed;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float RollingSpeed;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float RollingVelocityRate;
};
