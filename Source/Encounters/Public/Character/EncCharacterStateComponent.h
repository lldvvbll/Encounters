// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Components/ActorComponent.h"
#include "EncCharacterStateComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FonHpIsZeroDelegate);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ENCOUNTERS_API UEncCharacterStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEncCharacterStateComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetDamage(float NewDamage);

public:
	FonHpIsZeroDelegate OnHpIsZero;

private:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = State, Meta = (AllowPrivateAccess = true))
	float CurrentHP;

	float MAX_HP = 100.0f;
};
