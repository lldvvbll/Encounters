// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsInAttackRange.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("IsInAttackRange");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr, false);

	APlayerCharacter* Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEncAIController::TargetKey));
	return_if(Target == nullptr, false);
		
	return (Target->GetDistanceTo(NpcChar) <= NpcChar->GetAttackRange());
}
