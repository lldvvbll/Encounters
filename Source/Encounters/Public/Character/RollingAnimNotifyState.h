// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RollingAnimNotifyState.generated.h"

class AEncCharacter;

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API URollingAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	AEncCharacter* EncChar = nullptr;
	FVector Direction = FVector::ZeroVector;
	float RollingSpeed = 0.0f;
	float RollingForceScale = 0.0f;
	float RemainTime = 0.0f;
};
