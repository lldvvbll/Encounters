// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncAnimInstance.h"

UEncAnimInstance::UEncAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
}

void UEncAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	APawn* Pawn = TryGetPawnOwner();
	if (!::IsValid(Pawn))
		return;

	CurrentPawnSpeed = Pawn->GetVelocity().Size();
}
