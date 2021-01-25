// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINTARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 450.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &APlayerCharacter::Turn);

	PlayerInputComponent->BindAction(TEXT("Roll"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Roll);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Ragdoll"), EInputEvent::IE_Pressed, this, &APlayerCharacter::StartRagdoll);
	PlayerInputComponent->BindAction(TEXT("Defense"), EInputEvent::IE_Pressed, this, &APlayerCharacter::DefenseUp);
	PlayerInputComponent->BindAction(TEXT("Defense"), EInputEvent::IE_Released, this, &APlayerCharacter::DefenseDown);
}

void APlayerCharacter::MoveForward(float NewAxisValue)
{
	if (bRagdoll)
		return;

	if (bAttacking)
	{
		SavedInput.X = NewAxisValue;
		return;
	}

	if (bRolling)
		return;

	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void APlayerCharacter::MoveRight(float NewAxisValue)
{
	if (bRagdoll)
		return;

	if (bAttacking)
	{
		SavedInput.Y = NewAxisValue;
		return;
	}

	if (bRolling)
		return;

	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void APlayerCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void APlayerCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}
