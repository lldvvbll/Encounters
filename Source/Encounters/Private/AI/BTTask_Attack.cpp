// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Attack.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Attack::UBTTask_Attack()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NpcChar = Cast<ANpcCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	if (NpcChar == nullptr)
		return EBTNodeResult::Failed;

	//if (!NpcChar->StartComboAttack(2))
	if (!NpcChar->Attack())
		return EBTNodeResult::Failed;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto NpcChar = Cast<ANpcCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEncAIController::TargetKey));
	if (NpcChar == nullptr || Target == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (Target->IsDead())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else if (!NpcChar->IsAttacking())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
