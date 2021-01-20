// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Defense.h"
#include "EncAIController.h"
#include "Character/EncCharacter.h"


EBTNodeResult::Type UBTTask_Defense::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Char = Cast<AEncCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (Char == nullptr)
		return EBTNodeResult::Failed;

	Char->DefenseUp();

	return EBTNodeResult::InProgress;
}