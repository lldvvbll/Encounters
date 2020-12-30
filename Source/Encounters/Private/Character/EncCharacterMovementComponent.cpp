// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterMovementComponent.h"

UEncCharacterMovementComponent::UEncCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	RollingDuration = 0.3f;
	RollingAfterDelay = 0.2f;
	RollingForceScale = 4000000.0f;
}

void UEncCharacterMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!HasValidData() || ShouldSkipUpdate(DeltaTime))
		return;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRolling)
	{
		RollingRemainTime -= DeltaTime;
		if (RollingRemainTime < 0.0f || FMath::IsNearlyZero(RollingRemainTime))
		{
			EndRolling();
		}
		else if (RollingRemainTime >= RollingAfterDelay)
		{
			float Scale = IsFalling() ? (RollingForceScale / 10.0f) : RollingForceScale;
			AddForce(RollingDirection * Scale);
		}
		else
		{
			Launch(FVector(0.0f, 0.0f, Velocity.Z));
		}
	}
}

bool UEncCharacterMovementComponent::CanRolling() const
{
	if (bRolling || IsFalling())
		return false;

	return true;
}

bool UEncCharacterMovementComponent::IsRolling() const
{
	return bRolling;
}

void UEncCharacterMovementComponent::Rolling(const FVector& Direction)
{
	bRolling = true;
	RollingRemainTime = RollingDuration + RollingAfterDelay;
	RollingDirection = Direction;
}

void UEncCharacterMovementComponent::EndRolling()
{
	bRolling = false;
	RollingRemainTime = 0.0f;
	RollingDirection = FVector::ZeroVector;
}
