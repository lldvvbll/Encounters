// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsShovedOnBlocking.h"

UBTDecorator_IsShovedOnBlocking::UBTDecorator_IsShovedOnBlocking()
{
	NodeName = TEXT("IsShovedOnBlocking");
}

bool UBTDecorator_IsShovedOnBlocking::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr, false);

	return NpcChar->IsShovedOnBlocking();
}