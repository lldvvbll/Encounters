// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"
#include "EncPlayerState.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINTARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLockOnTarget)
	{
		if (LockedOnTarget.IsValid() && !LockedOnTarget->IsDead())
		{
			FVector TargetPos = LockedOnTarget->GetActorLocation();
			if ((TargetPos - GetActorLocation()).SizeSquared() < LockOnDistanceMaxSquared)
			{
				FVector Dir = TargetPos - GetCameraRotationPivot();
				Dir.Normalize();
				GetController()->SetControlRotation(Dir.Rotation());
			}			
			else
			{
				ReleaseLockOn();
			}
		}
		else
		{
			ReleaseLockOn();
		}		
	}
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AEncPlayerState* EncPlayerState = GetPlayerStateChecked<AEncPlayerState>())
	{
		EncPlayerState->SetCharacterState(CharacterState);
	}
}

void APlayerCharacter::UnPossessed()
{
	Super::UnPossessed();

	if (AEncPlayerState* EncPlayerState = GetPlayerState<AEncPlayerState>())
	{
		EncPlayerState->SetCharacterState(nullptr);
	}
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
	PlayerInputComponent->BindAction(TEXT("Guard"), EInputEvent::IE_Pressed, this, &APlayerCharacter::Guard);
	PlayerInputComponent->BindAction(TEXT("Guard"), EInputEvent::IE_Released, this, &APlayerCharacter::GuardDown);
	PlayerInputComponent->BindAction(TEXT("LockOn"), EInputEvent::IE_Pressed, this, &APlayerCharacter::LockOn);
}

bool APlayerCharacter::IsLockOnTarget() const
{
	return bLockOnTarget;
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
	if (!bLockOnTarget)
	{
		AddControllerPitchInput(NewAxisValue);
	}	
}

void APlayerCharacter::Turn(float NewAxisValue)
{
	if (!bLockOnTarget)
	{
		AddControllerYawInput(NewAxisValue);
	}	
}

FVector APlayerCharacter::GetCameraRotationPivot() const
{
	// 스프링암의 원점을 카메라 회전 중심으로 하자.
	return SpringArm->GetComponentLocation();
}

void APlayerCharacter::LockOn()
{
	if (bLockOnTarget)
	{
		ReleaseLockOn();
	}
	else
	{
		AController* CharController = GetController();

		TWeakObjectPtr<AEncCharacter> TargetPtr = FindLockOnTarget();
		if (TargetPtr.IsValid())
		{
			FVector Dir = TargetPtr->GetActorLocation() - GetCameraRotationPivot();
			Dir.Normalize();

			FRotator Rot = Dir.Rotation();
			Rot.Pitch = 0.0f;
			SetActorRotation(Rot);

			bLockOnTarget = true;
			LockedOnTarget = TargetPtr; 

			UCharacterMovementComponent* CharMovement = GetCharacterMovement();
			CharMovement->bOrientRotationToMovement = false;
			CharMovement->bUseControllerDesiredRotation = true;
		}
		else
		{
			FRotator CharRot = GetActorRotation();
			CharRot.Pitch = CharController->GetControlRotation().Pitch;
			CharController->SetControlRotation(CharRot);
		}
	}
}

void APlayerCharacter::ReleaseLockOn()
{
	bLockOnTarget = false;
	LockedOnTarget.Reset();

	UCharacterMovementComponent* CharMovement = GetCharacterMovement();
	CharMovement->bOrientRotationToMovement = true;
	CharMovement->bUseControllerDesiredRotation = false;
}

TWeakObjectPtr<AEncCharacter> APlayerCharacter::FindLockOnTarget() const
{
	TWeakObjectPtr<AEncCharacter> TargetPtr;

	FVector CharPos = GetActorLocation();

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, this);
	if (GetWorld()->OverlapMultiByChannel(OverlapResults, CharPos, FQuat::Identity, 
		ECollisionChannel::ECC_GameTraceChannel2, FCollisionShape::MakeSphere(LockOnDistanceMax), CollisionQueryParam))
	{
		FVector CharForward = GetActorForwardVector();
		FVector CamPos = Camera->GetComponentLocation();
		FVector CamForward = Camera->GetForwardVector();

		TArray<FLockOnCandidate> Candidates;
		Candidates.Empty(OverlapResults.Num());
		for (auto& Result : OverlapResults)
		{
			if (!Result.Actor.IsValid())
				continue;

			AEncCharacter* Target = CastChecked<AEncCharacter>(Result.Actor);
			if (Target == nullptr)
				continue;

			FLockOnCandidate Candidate;

			FVector TargetPos = Target->GetActorLocation();

			FVector DirCharToTarget = TargetPos - CharPos;
			Candidate.DistanceSquared = DirCharToTarget.SizeSquared();

			DirCharToTarget.Normalize();
			Candidate.bFrontOfChar = (FVector::DotProduct(CharForward, DirCharToTarget) > KINDA_SMALL_NUMBER);

			FVector DirCamToTarget = TargetPos - CamPos;
			DirCamToTarget.Normalize();
			Candidate.bFrontOfCam = (FVector::DotProduct(CamForward, DirCamToTarget) > KINDA_SMALL_NUMBER);

			Candidate.TargetPtr = Target;

			Candidates.Emplace(Candidate);
		}

		if (Candidates.Num() > 0)
		{
			Candidates.Sort(
				[](const FLockOnCandidate& Left, const FLockOnCandidate& Right)
				{
					if (Left.bFrontOfChar)
					{
						if (!Right.bFrontOfChar)
							return true;	// Left는 캐릭터 전방인데 Right는 후방이다. Left 우선
					}
					else
					{
						if (Right.bFrontOfChar)
							return false;	// Left는 캐릭터 후방인데 Right는 전방이다. Right 우선
					}

					if (Left.bFrontOfCam)
					{
						if (!Right.bFrontOfCam)
							return true;	// Left는 카메라 전방인데 Right는 후방이다. Left 우선
					}
					else
					{
						if (!Right.bFrontOfCam)
							return false;	// Left는 카메라 후방인데 Right는 전방이다. Right 우선
					}

					// 거리가 가까운게 우선
					return Left.DistanceSquared < Right.DistanceSquared;
				});
		}

		TargetPtr = Candidates[0].TargetPtr;
	}

	return TargetPtr;
}
