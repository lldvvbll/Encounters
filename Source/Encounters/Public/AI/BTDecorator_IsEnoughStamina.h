// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsEnoughStamina.generated.h"

UCLASS()
class ENCOUNTERS_API UBTDecorator_IsEnoughStamina : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsEnoughStamina();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
