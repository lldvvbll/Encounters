// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "AIController.h"
#include "EncAIController.generated.h"

class UBehaviorTree;
class UBlackboardData;

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API AEncAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AEncAIController();

	virtual void OnPossess(APawn* InPawn) override;
	
private:
	UPROPERTY(EditAnywhere, Category = AI, Meta = (AllowPrivateAccess = true))
	UBehaviorTree* BtAsset;

	UPROPERTY(EditAnywhere, Category = AI, Meta = (AllowPrivateAccess = true))
	UBlackboardData* BbAsset;
};
