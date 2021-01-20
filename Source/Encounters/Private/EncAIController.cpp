// Fill out your copyright notice in the Description page of Project Settings.


#include "EncAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"

AEncAIController::AEncAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_Data(
		TEXT("/Game/Encounters/AI/BB_Exam.BB_Exam"));
	if (BB_Data.Succeeded())
	{
		BbAsset = BB_Data.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_OBJECT(
		TEXT("/Game/Encounters/AI/BT_Exam.BT_Exam"));
	if (BT_OBJECT.Succeeded())
	{
		BtAsset = BT_OBJECT.Object;
	}
}

void AEncAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(BbAsset, Blackboard))
	{
		if (!RunBehaviorTree(BtAsset))
		{
			LOG(Error, TEXT("AIController couldn't run behavior tree!"));
		}
	}
}
