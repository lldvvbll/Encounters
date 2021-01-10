// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttackTracerAnimNotifyState.h"
#include "Character/EncCharacter.h"
#include "Items/Weapon.h"
#include "DrawDebugHelpers.h"

void UAttackTracerAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	return_if(MeshComp == nullptr);

	Player = MeshComp->GetOwner<AEncCharacter>();
	return_if(Player == nullptr);

	Weapon = Player->GetCurrentWeapon();
	return_if(Weapon == nullptr);

	LastAttackBoxPos = Weapon->GetAttackBoxSocketPos();
}

void UAttackTracerAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (Player == nullptr || Weapon == nullptr)
		return;

	FVector CurPos = Weapon->GetAttackBoxSocketPos();

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, Player);
	Player->GetWorld()->SweepMultiByChannel(HitResults, LastAttackBoxPos, CurPos, Weapon->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_EngineTraceChannel2, FCollisionShape::MakeBox(Weapon->GetAttackBoxHalfExtent()), Params);

	for (auto& Result : HitResults)
	{
		if (!Result.Actor.IsValid())
			continue;

		if (HitActors.Contains(Result.Actor))
			continue;

		HitActors.Add(Result.Actor);

		Player->GiveAttackDamage(Result.Actor);
	}

#if ENABLE_DRAW_DEBUG
	if (Weapon->IsShowAttackBoxInAttack())
	{
		Weapon->DrawAttackBox();
	}
#endif

	LastAttackBoxPos = CurPos;
}

void UAttackTracerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	HitActors.Empty();
}
