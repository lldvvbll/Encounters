// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Character/EncCharacter.h"
#include "NpcCharacter.generated.h"

class UBehaviorTree;
class UBlackboardData;
class UNpcDataAsset;
class ANpcCharacter;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNpcDeadDelegate, ANpcCharacter*);

UCLASS()
class ENCOUNTERS_API ANpcCharacter : public AEncCharacter
{
	GENERATED_BODY()
	
public:
	ANpcCharacter();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void RotateBySavedInput() override;

	virtual void Dead() override;

	UBehaviorTree* GetBehaviorTree() const;
	UBlackboardData* GetBlackboardData() const;

	void SetNpcDataAsset(UNpcDataAsset* DataAsset);

	float GetDetectionRange() const;
	float GetAttackRange() const;

public:
	FOnNpcDeadDelegate OnNpcDead;

private:
	UPROPERTY(VisibleAnywhere, Category = UI, Meta = (AllowPrivateAccess = true))
	UWidgetComponent* HpBarWidget;

	UPROPERTY(VisibleAnywhere, Category = DataAsset, Meta = (AllowPrivateAccess = true))
	UNpcDataAsset* NpcDataAsset;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 RemainComboCount;
};
