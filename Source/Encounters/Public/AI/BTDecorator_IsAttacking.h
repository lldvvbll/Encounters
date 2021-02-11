// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsAttacking.generated.h"

UCLASS()
class ENCOUNTERS_API UBTDecorator_IsAttacking : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_IsAttacking();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
