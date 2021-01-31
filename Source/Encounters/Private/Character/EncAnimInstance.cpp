// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncAnimInstance.h"
#include "Character/EncCharacter.h"

UEncAnimInstance::UEncAnimInstance()
{
	static ConstructorHelpers::FObjectFinder<UAnimMontage> ATTACK_MONTAGE(
		TEXT("/Game/Encounters/Characters/Animations/Encounters_Skeleton_Montage.Encounters_Skeleton_Montage"));
	if (ATTACK_MONTAGE.Succeeded())
	{
		AttackMontage = ATTACK_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> ROLLING_MONTAGE(
		TEXT("/Game/Encounters/Characters/Animations/RollingAnimMontage.RollingAnimMontage"));
	if (ROLLING_MONTAGE.Succeeded())
	{
		RollingMontage = ROLLING_MONTAGE.Object;
	}
}

void UEncAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEncCharacter* Char = Cast<AEncCharacter>(TryGetPawnOwner());
	if (!::IsValid(Char))
		return;

	FVector CharVelocity = Char->GetVelocity();
	CurrentPawnSpeed = CharVelocity.Size();
	IsRolling = Char->IsRolling();
	IsInAir = IsRolling ? false : Char->IsFalling();
	IsGuarding = Char->IsGuarding();
	IsLockOnTarget = Char->IsLockOnTarget();
	if (IsLockOnTarget)
	{
		Direction = CalculateDirection(CharVelocity, Char->GetActorRotation());
	}
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

bool UEncAnimInstance::IsAttackMontage(UAnimMontage* Montage)
{
	return (Montage != nullptr &&  Montage == AttackMontage);
}

void UEncAnimInstance::PlayRollingMontage(float PlayRate)
{
	Montage_Play(RollingMontage, PlayRate);
}

void UEncAnimInstance::StopRollingMontage()
{
	Montage_Stop(0.1f, RollingMontage);
}

bool UEncAnimInstance::IsRollingMontage(UAnimMontage* Montage)
{
	return (Montage != nullptr && Montage == RollingMontage);
}

void UEncAnimInstance::SetGuardSpeed(float NewSpeed)
{
	GuardSpeed = NewSpeed;
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

void UEncAnimInstance::AnimNotify_GuardUp()
{
	OnGuardUp.Broadcast();
}
