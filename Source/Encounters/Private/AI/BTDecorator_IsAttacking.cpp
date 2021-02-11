// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsAttacking.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"

UBTDecorator_IsAttacking::UBTDecorator_IsAttacking()
{
	NodeName = TEXT("IsAttacking");
}

bool UBTDecorator_IsAttacking::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr, false);

	return NpcChar->IsAttacking();
}
