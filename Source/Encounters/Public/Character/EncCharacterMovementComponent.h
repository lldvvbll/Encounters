// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EncCharacterMovementComponent.generated.h"

class AEncCharacter;

/**
 * 
 */
UCLASS()
class ENCOUNTERS_API UEncCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()	

public:
	UEncCharacterMovementComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void PostLoad() override;
	virtual void SetUpdatedComponent(USceneComponent* NewUpdatedComponent) override;

	bool CanRolling() const;
	bool IsRolling() const;
	void Roll(const FVector& Direction);
	void EndRoll();

	AEncCharacter* GetEncCharacterOwner();

protected:
	UPROPERTY(Transient, DuplicateTransient)
	AEncCharacter* EncCharacterOwner;

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
