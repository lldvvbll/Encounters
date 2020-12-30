// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncAnimInstance.h"
#include "Character/EncCharacter.h"

UEncAnimInstance::UEncAnimInstance()
{
	CurrentPawnSpeed = 0.0f;
	IsRolling = false;
}

void UEncAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AEncCharacter* Char = Cast<AEncCharacter>(TryGetPawnOwner());
	if (!::IsValid(Char))
		return;

	CurrentPawnSpeed = Char->GetVelocity().Size();
	IsRolling = Char->IsRolling();
	IsInAir = IsRolling ? false : Char->IsFalling();
}
