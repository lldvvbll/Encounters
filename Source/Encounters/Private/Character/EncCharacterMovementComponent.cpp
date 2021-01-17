// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacterMovementComponent.h"
#include "Character/EncCharacter.h"

FVector UEncCharacterMovementComponent::ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity, const FVector& CurrentVelocity) const
{
    FVector Result = Super::ConstrainAnimRootMotionVelocity(RootMotionVelocity, CurrentVelocity);

    AEncCharacter* Char = Cast<AEncCharacter>(GetCharacterOwner());
    if (Char != nullptr)
    {
        float Rate = Char->GetCurrentRootMotionVelocityRate();
        Result.X *= Rate;
        Result.Y *= Rate;
    }

    return Result;
}