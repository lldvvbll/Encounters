// Fill out your copyright notice in the Description page of Project Settings.


#include "EncAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Character/NpcCharacter.h"


void AEncAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	auto NpcChar = Cast<ANpcCharacter>(InPawn);
	return_if(NpcChar == nullptr);

	if (UseBlackboard(NpcChar->GetBlackboardData(), Blackboard))
	{
		if (!RunBehaviorTree(NpcChar->GetBehaviorTree()))
		{
			LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}	
}
