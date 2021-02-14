// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckStamina.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/EncCharacterStateComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckStamina::UBTService_CheckStamina()
{
	NodeName = TEXT("CheckStamina");
	Interval = 1.0f;
}

void UBTService_CheckStamina::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	UEncCharacterStateComponent* StateComp = NpcChar->GetCharacterStateComponent();
	return_if(BlackboardComp == nullptr || StateComp == nullptr);

	if (BlackboardComp->GetValueAsBool(AEncAIController::RecoveryStaminaKey))
	{
		float CurRecoveryStaminaAmount = BlackboardComp->GetValueAsFloat(AEncAIController::RecoveryStaminaAmountKey);
		if (StateComp->GetStaminaRatio() > CurRecoveryStaminaAmount)
		{
			BlackboardComp->SetValueAsBool(AEncAIController::RecoveryStaminaKey, false);
			BlackboardComp->SetValueAsFloat(AEncAIController::RecoveryStaminaAmountKey, 0.0f);
		}
	}
	else
	{
		if (StateComp->GetStaminaRatio() < 0.1f)
		{
			BlackboardComp->SetValueAsBool(AEncAIController::RecoveryStaminaKey, true);

			float RandomAmount = static_cast<float>(FMath::RandRange(3, 9)) / 10.0f;
			BlackboardComp->SetValueAsFloat(AEncAIController::RecoveryStaminaAmountKey, RandomAmount);
		}
	}	
}
