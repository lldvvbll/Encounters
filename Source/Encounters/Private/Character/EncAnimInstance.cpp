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

	static ConstructorHelpers::FObjectFinder<UAnimMontage> SHOVED_ON_BLOCKING_MONTAGE(
		TEXT("/Game/Encounters/Characters/Animations/ShovedOnBlockingAnimMontage.ShovedOnBlockingAnimMontage"));
	if (SHOVED_ON_BLOCKING_MONTAGE.Succeeded())
	{
		ShovedOnBlockingMontage = SHOVED_ON_BLOCKING_MONTAGE.Object;
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> FLINCH_MONTAGE(
		TEXT("/Game/Encounters/Characters/Animations/FlinchAnimMontage.FlinchAnimMontage"));
	if (FLINCH_MONTAGE.Succeeded())
	{
		FlinchMontage = FLINCH_MONTAGE.Object;
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
	IsShovedOnBlocking = Char->IsShovedOnBlocking();
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

bool UEncAnimInstance::IsAttackMontage(UAnimMontage* Montage)
{
	return (Montage != nullptr &&  Montage == AttackMontage);
}

void UEncAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	return_if(!Montage_IsPlaying(AttackMontage));

	Montage_JumpToSection(GetAttackMontageSectionName(NewSection));
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

void UEncAnimInstance::PlayShovedOnBlockingMontage(float PlayRate)
{
	Montage_Play(ShovedOnBlockingMontage, PlayRate);
}

void UEncAnimInstance::StopShovedOnBlockingMontage()
{
	Montage_Stop(0.1f, ShovedOnBlockingMontage);
}

bool UEncAnimInstance::IsShovedOnBlockingMontage(UAnimMontage* Montage)
{
	return (Montage != nullptr && Montage == ShovedOnBlockingMontage);
}

void UEncAnimInstance::PlayFlinchMontage(float PlayRate)
{
	Montage_Play(FlinchMontage, PlayRate);
}

void UEncAnimInstance::StopFlinchMontage()
{
	Montage_Stop(0.1f, FlinchMontage);
}

bool UEncAnimInstance::IsFlinchMontage(UAnimMontage* Montage)
{
	return (Montage != nullptr && Montage == FlinchMontage);
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

void UEncAnimInstance::AnimNotify_BeginAvoidance()
{
	OnBeginAvoidance.Broadcast();
}

void UEncAnimInstance::AnimNotify_EndAvoidance()
{
	OnEndAvoidance.Broadcast();
}

void UEncAnimInstance::AnimNotify_GuardUp()
{
	OnGuardUp.Broadcast();
}

FName UEncAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}
