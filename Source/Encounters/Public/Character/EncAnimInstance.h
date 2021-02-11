// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimInstance.h"
#include "EncAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnComboEnableDelegate);
DECLARE_MULTICAST_DELEGATE(FOnComboCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBeginAvoidanceDelegate);
DECLARE_MULTICAST_DELEGATE(FOnEndAvoidanceDelegate);
DECLARE_MULTICAST_DELEGATE(FOnGuardUpDelegate);

UCLASS()
class ENCOUNTERS_API UEncAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEncAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(float PlayRate);
	void StopAttackMontage();
	bool IsAttackMontage(UAnimMontage* Montage);
	void JumpToAttackMontageSection(int32 NewSection);

	void PlayRollingMontage(float PlayRate);
	void StopRollingMontage();
	bool IsRollingMontage(UAnimMontage* Montage);

	void PlayShovedOnBlockingMontage(float PlayRate);
	void StopShovedOnBlockingMontage();
	bool IsShovedOnBlockingMontage(UAnimMontage* Montage);

	void PlayFlinchMontage(float PlayRate);
	void StopFlinchMontage();
	bool IsFlinchMontage(UAnimMontage* Montage);

	void SetGuardSpeed(float NewSpeed);

private:
	UFUNCTION()
	void AnimNotify_ComboEnable();

	UFUNCTION()
	void AnimNotify_ComboCheck();

	UFUNCTION()
	void AnimNotify_BeginAvoidance();

	UFUNCTION()
	void AnimNotify_EndAvoidance();

	UFUNCTION()
	void AnimNotify_GuardUp();

	FName GetAttackMontageSectionName(int32 Section);

public:
	FOnComboEnableDelegate OnComboEnable;
	FOnComboCheckDelegate OnComboCheck;
	FOnGuardUpDelegate OnGuardUp;
	FOnBeginAvoidanceDelegate OnBeginAvoidance;
	FOnEndAvoidanceDelegate OnEndAvoidance;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsRolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsGuarding;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float GuardSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsLockOnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsShovedOnBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* RollingMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* ShovedOnBlockingMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* FlinchMontage;
};
