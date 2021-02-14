// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckGuard.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_CheckGuard::UBTService_CheckGuard()
{
	NodeName = TEXT("CheckGuard");
	Interval = 0.5f;
}

void UBTService_CheckGuard::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr);

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	return_if(BlackboardComp == nullptr);

	if (NpcChar->IsGuarding())
	{
		APlayerCharacter* Target = Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject(AEncAIController::TargetKey));
		if (Target == nullptr)
		{
			NpcChar->GuardDown();
		}
		else if (Target->GetDistanceTo(NpcChar) > 200.0f)
		{
			NpcChar->GuardDown();
		}
	}
	else
	{
		APlayerCharacter* Target = Cast<APlayerCharacter>(BlackboardComp->GetValueAsObject(AEncAIController::TargetKey));
		if (Target != nullptr && Target->GetDistanceTo(NpcChar) <= 200.0f)
		{
			NpcChar->Guard();
		}
	}
}
