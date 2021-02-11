// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_Detect.h"
#include "EncAIController.h"
#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ANpcCharacter* NpcChar = OwnerComp.GetAIOwner()->GetPawn<ANpcCharacter>();
	return_if(NpcChar == nullptr);

	UWorld* World = NpcChar->GetWorld();
	return_if(World == nullptr);

	FVector Center = NpcChar->GetActorLocation();
	float DetectionRange = NpcChar->GetDetectionRange();

	UBlackboardComponent* BlackboardComp = OwnerComp.GetBlackboardComponent();
	BlackboardComp->SetValueAsObject(AEncAIController::TargetKey, nullptr);

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, NpcChar);
	if (!World->OverlapMultiByChannel(OverlapResults, Center, FQuat::Identity, ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(DetectionRange), CollisionQueryParam))
		return;

	APlayerCharacter* PlayerChar = Cast<APlayerCharacter>(OverlapResults[0].GetActor());
	if (PlayerChar != nullptr && PlayerChar->GetController()->IsPlayerController())
	{
		BlackboardComp->SetValueAsObject(AEncAIController::TargetKey, PlayerChar);

#if ENABLE_DRAW_DEBUG
		DrawDebugSphere(World, Center, DetectionRange, 16, FColor::Green, false, 0.2f);
		DrawDebugPoint(World, PlayerChar->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
		DrawDebugLine(World, NpcChar->GetActorLocation(), PlayerChar->GetActorLocation(),
			FColor::Blue, false, 0.2f);
#endif // ENABLE_DRAW_DEBUG

	}
}
