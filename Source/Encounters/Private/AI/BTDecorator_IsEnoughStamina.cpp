// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsEnoughStamina.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"

UBTDecorator_IsEnoughStamina::UBTDecorator_IsEnoughStamina()
{
	NodeName = TEXT("IsEnoughStamina");
}

bool UBTDecorator_IsEnoughStamina::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr, false);

	return NpcChar->GetCurrentStamina() >= NpcChar->GetStaminaForAttack();
}
