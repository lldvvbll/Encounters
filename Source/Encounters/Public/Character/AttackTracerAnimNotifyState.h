// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackTracerAnimNotifyState.generated.h"

class AEncCharacter;
class AWeapon;

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API UAttackTracerAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	AEncCharacter* Player = nullptr;
	AWeapon* Weapon = nullptr;
	FVector LastAttackBoxPos = FVector::ZeroVector;
	TArray<AActor*> HitActors;

};
