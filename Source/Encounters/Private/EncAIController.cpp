// Fill out your copyright notice in the Description page of Project Settings.


#include "EncAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "Character/NpcCharacter.h"

const FName AEncAIController::TargetKey(TEXT("Target"));
const FName AEncAIController::RecoveryStaminaRatioKey(TEXT("RecoveryStaminaRatio"));

void AEncAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	RunAI();
}

void AEncAIController::RunAI()
{
	auto NpcChar = Cast<ANpcCharacter>(GetPawn());
	return_if(NpcChar == nullptr);

	if (UseBlackboard(NpcChar->GetBlackboardData(), Blackboard))
	{
		if (!RunBehaviorTree(NpcChar->GetBehaviorTree()))
		{
			LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}

void AEncAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	return_if(BehaviorTreeComponent == nullptr);

	BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
}