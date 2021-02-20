// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttackTracerAnimNotifyState.h"
#include "Character/EncCharacter.h"
#include "Items/Actors/Weapon.h"
#include "EncGameState.h"
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

	LastAttackBoxPos = Weapon->GetCollisionBoxPos();

	//FVector Dist = LastAttackBoxPos - EncChar->GetActorLocation();
	//MaxAttackRange = Dist.Size2D();
	//MinAttackRange = Dist.Size2D();
}

void UAttackTracerAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);

	if (EncChar == nullptr || Weapon == nullptr)
		return;

	FVector CurPos = Weapon->GetCollisionBoxPos();

	TArray<FHitResult> HitResults;
	FCollisionQueryParams Params(NAME_None, false, EncChar);
	EncChar->GetWorld()->SweepMultiByChannel(HitResults, LastAttackBoxPos, CurPos, Weapon->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_GameTraceChannel2, Weapon->GetCollisionBox(), Params);

	for (auto& Result : HitResults)
	{
		if (!Result.Actor.IsValid())
			continue;

		if (HitActors.Contains(Result.Actor))
			continue;

		HitActors.Add(Result.Actor);

		EncChar->GiveAttackDamage(Result.Actor);
	}

#if ENABLE_DRAW_DEBUG
	if (auto GameState = EncChar->GetWorld()->GetGameState<AEncGameState>())
	{
		if (GameState->IsDrawDebugWeaponCollisionBox())
		{
			Weapon->DrawDebugCollisionBox();
		}		
	}
#endif

	LastAttackBoxPos = CurPos;

	//FVector Dist = LastAttackBoxPos - EncChar->GetActorLocation();
	//MaxAttackRange = FMath::Max(MaxAttackRange, Dist.Size2D());
	//MinAttackRange = FMath::Min(MinAttackRange, Dist.Size2D());
}

void UAttackTracerAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	HitActors.Empty();

	//LOG(Warning, TEXT("Min: %f, Max: %f"), MinAttackRange, MaxAttackRange);
}
