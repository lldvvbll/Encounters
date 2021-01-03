// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimInstance.h"
#include "EncAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegate);
DECLARE_MULTICAST_DELEGATE(FOnComboEnableDelegate);
DECLARE_MULTICAST_DELEGATE(FOnComboCheckDelegate);

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
	void JumpToAttackMontageSection(int32 NewSection);

private:
	UFUNCTION()
	void AnimNotify_AttackHitCheck();

	UFUNCTION()
	void AnimNotify_ComboEnable();

	UFUNCTION()
	void AnimNotify_ComboCheck();

	FName GetAttackMontageSectionName(int32 Section);

public:
	FOnAttackHitCheckDelegate OnAttackHitCheck;
	FOnComboEnableDelegate OnComboEnable;
	FOnComboCheckDelegate OnComboCheck;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsRolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	bool IsInAir;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};
