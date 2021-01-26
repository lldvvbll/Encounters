// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimInstance.h"
#include "EncAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnComboEnableDelegate);
DECLARE_MULTICAST_DELEGATE(FOnComboCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnBeginGaurdDelegate);

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API UEncAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UEncAnimInstance();
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage(float PlayRate);
	void StopAttackMontage();
	void JumpToAttackMontageSection(int32 NewSection);
	bool IsAttackMontage(UAnimMontage* Montage);

	void PlayRollingMontage(float PlayRate);
	void StopRollingMontage();
	bool IsRollingMontage(UAnimMontage* Montage);

	void SetDefenseSpeed(float NewSpeed);

private:
	UFUNCTION()
	void AnimNotify_ComboEnable();

	UFUNCTION()
	void AnimNotify_ComboCheck();

	FName GetAttackMontageSectionName(int32 Section);

	UFUNCTION()
	void AnimNotify_BeginGaurd();

public:
	FOnComboEnableDelegate OnComboEnable;
	FOnComboCheckDelegate OnComboCheck;
	FOnBeginGaurdDelegate OnBeginGaurd;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsRolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsDefending;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float DefenseSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsLockOnTarget;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float Direction;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Montage, Meta = (AllowPrivateAccess = true))
	UAnimMontage* RollingMontage;
};
