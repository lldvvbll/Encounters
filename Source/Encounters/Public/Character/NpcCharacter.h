// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Character/EncCharacter.h"
#include "NpcCharacter.generated.h"

class UBehaviorTree;
class UBlackboardData;
class UNpcDataAsset;

UCLASS()
class ENCOUNTERS_API ANpcCharacter : public AEncCharacter
{
	GENERATED_BODY()
	
public:
	ANpcCharacter();

	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Dead() override;

	UBehaviorTree* GetBehaviorTree() const;
	UBlackboardData* GetBlackboardData() const;

	void SetCharacterAbilityByDataAsset(UNpcDataAsset* DataAsset) const;

	float GetDetectionRange() const;

private:
	UPROPERTY(VisibleAnywhere, Category = UI, Meta = (AllowPrivateAccess = true))
	UWidgetComponent* HpBarWidget;

	UPROPERTY(EditAnywhere, Category = AI, Meta = (AllowPrivateAccess = true))
	UBehaviorTree* BehaviorTree;

	UPROPERTY(EditAnywhere, Category = AI, Meta = (AllowPrivateAccess = true))
	UBlackboardData* BlackboardData;
};
