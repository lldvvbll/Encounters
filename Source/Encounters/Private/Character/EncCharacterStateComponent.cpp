// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterStateComponent.h"

UEncCharacterStateComponent::UEncCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	MaxHP = 1.0f;
	MaxStamina = 1.0f;
	RollingSpeed = 1.0f;
	RollingVelocityRate = 1.0f;
}

void UEncCharacterStateComponent::SetHP(float NewHP)
{
	CurrentHP = NewHP;
	OnHpChanged.Broadcast();
	if (CurrentHP < KINDA_SMALL_NUMBER)
	{
		OnHpIsZero.Broadcast();
	}
}

void UEncCharacterStateComponent::ModifyHP(float Amount)
{
	SetHP(FMath::Clamp<float>(CurrentHP + Amount, 0.0f, MaxHP));
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

void UEncCharacterStateComponent::SetStamina(float NewStamina)
{
	CurrentStamina = NewStamina;
	OnStaminaChanged.Broadcast();
}

void UEncCharacterStateComponent::ModifyStamina(float Amount)
{
	SetStamina(FMath::Clamp<float>(CurrentStamina + Amount, 0.0f, MaxStamina));
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

void UEncCharacterStateComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetHP(MaxHP);
	SetStamina(MaxStamina);
}
