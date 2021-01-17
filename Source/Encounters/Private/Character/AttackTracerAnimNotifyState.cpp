// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttackTracerAnimNotifyState.h"
#include "Character/EncCharacter.h"
#include "Items/Weapon.h"
#include "DrawDebugHelpers.h"

void UAttackTracerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	return_if(MeshComp == nullptr);

	EncChar = MeshComp->GetOwner<AEncCharacter>();
	if (EncChar == nullptr)
		return;

	Weapon = EncChar->GetCurrentWeapon();
	return_if(Weapon == nullptr);

	LastAttackBoxPos = Weapon->GetAttackBoxSocketPos();
}

void UAttackTracerAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (EncChar == nullptr || Weapon == nullptr)
		return;

	FVector CurPos = Weapon->GetAttackBoxSocketPos();

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, EncChar);
	EncChar->GetWorld()->SweepMultiByChannel(HitResults, LastAttackBoxPos, CurPos, Weapon->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeBox(Weapon->GetAttackBoxHalfExtent()), Params);

	for (auto& Result : HitResults)
	{
		if (!Result.Actor.IsValid())
			continue;

		if (HitActors.Contains(Result.Actor))
			continue;

		HitActors.Add(Result.Actor);

		EncChar->GiveAttackDamage(Result.Actor);
	}

	if (Weapon->IsShowAttackBoxInAttack())
	{
		Weapon->DrawAttackBox();
	}

	LastAttackBoxPos = CurPos;
}

void UAttackTracerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	HitActors.Empty();
}
