// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Defense.generated.h"

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API UBTTask_Defense : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
