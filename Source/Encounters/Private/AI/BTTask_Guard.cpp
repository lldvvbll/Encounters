// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Guard.h"
#include "EncAIController.h"
#include "Character/EncCharacter.h"


EBTNodeResult::Type UBTTask_Guard::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Char = Cast<AEncCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Char == nullptr)
		return EBTNodeResult::Failed;

	Char->Guard();

	return EBTNodeResult::InProgress;
}