// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckStamina.generated.h"

UCLASS()
class ENCOUNTERS_API UBTService_CheckStamina : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckStamina();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
