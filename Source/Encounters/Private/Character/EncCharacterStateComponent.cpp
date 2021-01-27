// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterStateComponent.h"

UEncCharacterStateComponent::UEncCharacterStateComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UEncCharacterStateComponent::SetDamage(float NewDamage)
{
	SetHP(FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, MAX_HP));
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

float UEncCharacterStateComponent::GetHpRatio() const
{
	return CurrentHP / MAX_HP;
}

void UEncCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UEncCharacterStateComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetHP(MAX_HP);
}
