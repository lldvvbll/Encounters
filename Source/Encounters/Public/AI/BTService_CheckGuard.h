// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CheckGuard.generated.h"

UCLASS()
class ENCOUNTERS_API UBTService_CheckGuard : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CheckGuard();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
