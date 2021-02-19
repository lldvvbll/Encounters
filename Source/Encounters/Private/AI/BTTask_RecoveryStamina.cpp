// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_RecoveryStamina.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_RecoveryStamina::UBTTask_RecoveryStamina()
{
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_RecoveryStamina::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NpcChar = Cast<ANpcCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (NpcChar == nullptr || BlackboardComp == nullptr)
		return EBTNodeResult::Failed;

	float RandomRatio = static_cast<float>(FMath::RandRange(5, 9)) / 10.0f;
	BlackboardComp->SetValueAsFloat(AEncAIController::RecoveryStaminaRatioKey, RandomRatio);

	return EBTNodeResult::InProgress;
}

void UBTTask_RecoveryStamina::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	auto NpcChar = Cast<ANpcCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (NpcChar == nullptr || BlackboardComp == nullptr)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}

	float TargetRatio = BlackboardComp->GetValueAsFloat(AEncAIController::RecoveryStaminaRatioKey);
	if (NpcChar->GetCurrentStaminaRatio() >= TargetRatio)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
