// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterStateComponent.h"

// Sets default values for this component's properties
UEncCharacterStateComponent::UEncCharacterStateComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

// Called when the game starts
void UEncCharacterStateComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UEncCharacterStateComponent::InitializeComponent()
{
	Super::InitializeComponent();

	CurrentHP = MAX_HP;
}

// Called every frame
void UEncCharacterStateComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UEncCharacterStateComponent::SetDamage(float NewDamage)
{
	CurrentHP = FMath::Clamp<float>(CurrentHP - NewDamage, 0.0f, MAX_HP);
	if (CurrentHP <= 0.0f)
	{
		OnHpIsZero.Broadcast();
	}
}

