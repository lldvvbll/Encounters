// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacter.h"
#include "Character/EncCharacterMovementComponent.h"
#include "Character/EncAnimInstance.h"

// Sets default values
AEncCharacter::AEncCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEncCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINTARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	
	IsAttacking = false;
	CanSaveAttack = false;
	bInputAttack = false;
	CurrentCombo = 0;
	MaxComboCount = 2;

	SpringArm->SetupAttachment(GetCapsuleComponent());
	Camera->SetupAttachment(SpringArm);

	SpringArm->TargetArmLength = 450.0f;
	SpringArm->bUsePawnControlRotation = true;
	SpringArm->bInheritPitch = true;
	SpringArm->bInheritRoll = true;
	SpringArm->bInheritYaw = true;
	SpringArm->bDoCollisionTest = true;
	bUseControllerRotationYaw = false;

	UCharacterMovementComponent* CharMovementComp = GetCharacterMovement();
	CharMovementComp->bOrientRotationToMovement = true;
	CharMovementComp->bUseControllerDesiredRotation = false;
	CharMovementComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	SkeletalMeshComp->SetRelativeLocationAndRotation(
		FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_DEFAULT(
		TEXT("/Game/Mannequin/Character/Mesh/SK_Mannequin.SK_Mannequin"));
	if (SK_DEFAULT.Succeeded())
	{
		SkeletalMeshComp->SetSkeletalMesh(SK_DEFAULT.Object);
	}

	SkeletalMeshComp->SetAnimationMode(EAnimationMode::AnimationBlueprint);

	static ConstructorHelpers::FClassFinder<UAnimInstance> ENC_ANIM(
		TEXT("/Game/Encounters/Characters/Animations/EncAnimBlueprint.EncAnimBlueprint_C"));
	if (ENC_ANIM.Succeeded())
	{
		SkeletalMeshComp->SetAnimInstanceClass(ENC_ANIM.Class);
	}
}

// Called when the game starts or when spawned
void AEncCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEncCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEncCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AEncCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AEncCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AEncCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AEncCharacter::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AEncCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &AEncCharacter::Turn);
	
	PlayerInputComponent->BindAction(TEXT("Roll"), EInputEvent::IE_Pressed, this, &AEncCharacter::Roll);
	PlayerInputComponent->BindAction(TEXT("Attack"), EInputEvent::IE_Pressed, this, &AEncCharacter::Attack);
}

void AEncCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EncCharacterMovement = Cast<UEncCharacterMovementComponent>(GetCharacterMovement());
	EncAnim = Cast<UEncAnimInstance>(GetMesh()->GetAnimInstance());
	if (EncAnim != nullptr)
	{
		EncAnim->OnMontageEnded.AddDynamic(this, &AEncCharacter::OnAttackMontageEnded);
		EncAnim->OnComboEnable.AddUObject(this, &AEncCharacter::OnComboEnable);
		EncAnim->OnComboCheck.AddUObject(this, &AEncCharacter::OnComboCheck);
	}
}

UEncCharacterMovementComponent* AEncCharacter::GetEncCharacterMovement() const
{
	return EncCharacterMovement;
}

bool AEncCharacter::IsRolling() const
{
	return (EncCharacterMovement != nullptr && EncCharacterMovement->IsRolling());
}

bool AEncCharacter::IsFalling() const
{
	return (EncCharacterMovement != nullptr && EncCharacterMovement->IsFalling());
}

void AEncCharacter::MoveForward(float NewAxisValue)
{
	if (IsRolling())
		return;

	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AEncCharacter::MoveRight(float NewAxisValue)
{
	if (IsRolling())
		return;

	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::Y), NewAxisValue);
}

void AEncCharacter::LookUp(float NewAxisValue)
{
	AddControllerPitchInput(NewAxisValue);
}

void AEncCharacter::Turn(float NewAxisValue)
{
	AddControllerYawInput(NewAxisValue);
}

void AEncCharacter::Roll()
{
	UEncCharacterMovementComponent* CharMovement = GetEncCharacterMovement();
	if (!CharMovement->CanRolling())
		return;

	FVector DirToMove = CharMovement->GetLastInputVector();
	if (DirToMove.IsNearlyZero())
		return;

	SetActorRotation(DirToMove.Rotation(), ETeleportType::TeleportPhysics);

	DirToMove.Normalize();
	CharMovement->Roll(DirToMove);
}

void AEncCharacter::Attack()
{
	if (IsAttacking)
	{
		if (CanSaveAttack)
		{
			bInputAttack = true;
		}
	}
	else
	{
		CurrentCombo = 1;
		bInputAttack = false;
		IsAttacking = true;

		EncAnim->PlayAttackMontage();
		EncAnim->JumpToAttackMontageSection(CurrentCombo);		
	}	
}

void AEncCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	CurrentCombo = 0;
	bInputAttack = false;
	IsAttacking = false;
}

void AEncCharacter::OnComboEnable()
{
	CanSaveAttack = true;
}

void AEncCharacter::OnComboCheck()
{
	CanSaveAttack = false;

	if (bInputAttack)
	{
		bInputAttack = false;

		++CurrentCombo;
		if (CurrentCombo > MaxComboCount)
		{
			CurrentCombo = 1;
		}

		EncAnim->JumpToAttackMontageSection(CurrentCombo);
	}
}
