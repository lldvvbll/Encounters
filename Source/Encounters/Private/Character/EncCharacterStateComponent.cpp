// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterStateComponent.h"

UEncCharacterStateComponent::UEncCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	MaxHP = 1.0f;
	MaxStamina = 1.0f;
	StaminaRecoverySpeed = 1.0f;
	bStaminaRecovery = true;
	RollingSpeed = 1.0f;
	RollingVelocityRate = 1.0f;
}

void UEncCharacterStateComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bHpRecovery && CurrentHP < MaxHP)
	{
		SetHP(FMath::FInterpConstantTo(CurrentHP, MaxHP, DeltaTime, HpRecoverySpeed));
	}

	if (bStaminaRecovery && CurrentStamina < MaxStamina)
	{
		SetStamina(FMath::FInterpConstantTo(CurrentStamina, MaxStamina, DeltaTime, StaminaRecoverySpeed));
	}
}

void UEncCharacterStateComponent::SetAttackPower(float NewAttackPower)
{
	AttackPower = NewAttackPower;
}

float UEncCharacterStateComponent::GetAttackPower() const
{
	return AttackPower;
}

void UEncCharacterStateComponent::SetHP(float NewHP)
{
	CurrentHP = FMath::Clamp<float>(NewHP, 0.0f, MaxHP);

	OnHpChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnHpIsZero.Broadcast();
	}
}

void UEncCharacterStateComponent::ModifyHP(float Amount)
{
	SetHP(CurrentHP + Amount);
}

float UEncCharacterStateComponent::GetHP() const
{
	return CurrentHP;
}

void UEncCharacterStateComponent::SetMaxHP(float NewHP)
{
	MaxHP = NewHP;
	OnMaxHpChanged.Broadcast();
}

float UEncCharacterStateComponent::GetMaxHP() const
{
	return MaxHP;
}

float UEncCharacterStateComponent::GetHpRatio() const
{
	return CurrentHP / MaxHP;
}

void UEncCharacterStateComponent::SetHpRecovery(bool bEnable)
{
	bHpRecovery = bEnable;
}

void UEncCharacterStateComponent::SetStamina(float NewStamina)
{
	CurrentStamina = FMath::Clamp<float>(NewStamina, 0.0f, MaxStamina);

	OnStaminaChanged.Broadcast();
}

void UEncCharacterStateComponent::ModifyStamina(float Amount)
{
	SetStamina(CurrentStamina + Amount);
}

float UEncCharacterStateComponent::GetStamina() const
{
	return CurrentStamina;
}

void UEncCharacterStateComponent::SetMaxStamina(float NewStamina)
{
	MaxStamina = NewStamina;
	OnMaxStaminaChanged.Broadcast();
}

float UEncCharacterStateComponent::GetMaxStamina() const
{
	return MaxStamina;
}

float UEncCharacterStateComponent::GetStaminaRatio() const
{
	return CurrentStamina / MaxStamina;
}

void UEncCharacterStateComponent::SetStaminaRecovery(bool bEnable)
{
	bStaminaRecovery = bEnable;
}

void UEncCharacterStateComponent::SetRollingSpeed(float NewRollingSpeed)
{
	RollingSpeed = NewRollingSpeed;
}

float UEncCharacterStateComponent::GetRolligSpeed() const
{
	return RollingSpeed;
}

void UEncCharacterStateComponent::SetRollingVelocityRate(float NewRate)
{
	RollingVelocityRate = NewRate;
}

float UEncCharacterStateComponent::GetRollingVelocityRate() const
{
	return RollingVelocityRate;
}

void UEncCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

	OnHpChanged.Broadcast();
}
