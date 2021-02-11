// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_TurnToTarget.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"

UBTTask_TurnToTarget::UBTTask_TurnToTarget()
{
	NodeName = TEXT("Turn");
}

EBTNodeResult::Type UBTTask_TurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto NpcChar = Cast<ANpcCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AEncAIController::TargetKey));
	if (NpcChar == nullptr || Target == nullptr)
		return EBTNodeResult::Failed;

	FVector LookVector = Target->GetActorLocation() - NpcChar->GetActorLocation();
	LookVector.Z = 0.0f;

	FRotator TargetRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	NpcChar->SetActorRotation(FMath::RInterpTo(NpcChar->GetActorRotation(), TargetRot, GetWorld()->GetDeltaSeconds(), 2.0f));

	return EBTNodeResult::Succeeded;
}
