// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncAnimInstance.h"
#include "Character/EncCharacter.h"

UEncAnimInstance::UEncAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsRolling = false;

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(
		TEXT("/Game/Encounters/Characters/Animations/Encounters_Skeleton_Montage.Encounters_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}
}

void UEncAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEncCharacter* Char = Cast<AEncCharacter>(TryGetPawnOwner());
	if (!::IsValid(Char))
		return;

	CurrentPawnSpeed = Char->GetVelocity().Size();
	IsRolling = Char->IsRolling();
	IsInAir = IsRolling ? false : Char->IsFalling();
}

void UEncAnimInstance::PlayAttackMontage(float PlayRate)
{
	Montage_Play(AttackMontage, PlayRate);
}

void UEncAnimInstance::StopAttackMontage()
{
	Montage_Stop(0.1f, AttackMontage);
}

void UEncAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	return_if(!Montage_IsPlaying(AttackMontage));

	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
}

void UEncAnimInstance::AnimNotify_ComboEnable()
{
	OnComboEnable.Broadcast();
}

void UEncAnimInstance::AnimNotify_ComboCheck()
{
	OnComboCheck.Broadcast();
}

FName UEncAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
