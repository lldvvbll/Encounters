// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/RollingAnimNotifyState.h"
#include "Character/EncCharacter.h"
#include "DrawDebugHelpers.h"

void URollingAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	return_if(MeshComp == nullptr);

	EncChar = MeshComp->GetOwner<AEncCharacter>();
	if (EncChar == nullptr)
		return;

	Direction = EncChar->GetActorForwardVector();
	//RollingSpeed = EncChar->GetRollingSpeed();
	//RollingForceScale = EncChar->GetRollingForceScale();
	RemainTime = TotalDuration / RollingSpeed;

	//LOG(Warning, TEXT("TotalDuration: %f"), TotalDuration);
}

void URollingAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	RemainTime -= FrameDeltaTime;
	LOG(Warning, TEXT("RemainTime: %f"), RemainTime);

	if (EncChar == nullptr)
		return;

	if (EncChar->IsFalling())
	{
		EncChar->LaunchCharacter(FVector::ZeroVector, true, false);
		return;
	}

	RollingForceScale = FMath::FInterpTo(RollingForceScale, 0.0f, FrameDeltaTime, 1.0f / RemainTime);
	EncChar->GetCharacterMovement()->AddForce(Direction * RollingForceScale);

	//LOG(Warning, TEXT("RollingForceScale: %f"), RollingForceScale);
	//DrawDebugPoint(EncChar->GetWorld(), EncChar->GetActorLocation(), 10.0f, FColor::Red, false, 10.0f);
}

void URollingAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	if (EncChar == nullptr)
		return;

	EncChar->LaunchCharacter(FVector::ZeroVector, true, false);

	//DrawDebugPoint(EncChar->GetWorld(), EncChar->GetActorLocation(), 10.0f, FColor::Blue, false, 10.0f);
}
