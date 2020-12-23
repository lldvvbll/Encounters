// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Animation/AnimInstance.h"
#include "EncAnimInstance.generated.h"

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

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float CurrentPawnSpeed;
};
