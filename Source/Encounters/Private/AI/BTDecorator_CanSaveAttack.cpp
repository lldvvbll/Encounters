// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_CanSaveAttack.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"

UBTDecorator_CanSaveAttack::UBTDecorator_CanSaveAttack()
{
	NodeName = TEXT("CanSaveAttack");
}

bool UBTDecorator_CanSaveAttack::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr, false);

	return NpcChar->CanSaveAttack();
}