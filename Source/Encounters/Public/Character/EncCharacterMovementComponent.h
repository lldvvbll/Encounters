// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EncCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API UEncCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()	

public:
	UEncCharacterMovementComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool CanRolling() const;
	bool IsRolling() const;
	void Rolling(const FVector& Direction);
	void EndRolling();

private:
	UPROPERTY(EditAnywhere, Category = "Character Movement: Rolling", Meta = (AllowPrivateAccess = true))
	float RollingDuration;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Rolling", Meta = (AllowPrivateAccess = true))
	float RollingForceScale;

	UPROPERTY(EditAnywhere, Category = "Character Movement: Rolling", Meta = (AllowPrivateAccess = true))
	float RollingAfterDelay;

	bool bRolling = false;
	float RollingRemainTime = 0.0f;
	FVector RollingDirection = FVector::ZeroVector;
};
