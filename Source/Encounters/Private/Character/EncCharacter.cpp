// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacter.h"
#include "Character/EncCharacterMovementComponent.h"
#include "Character/EncAnimInstance.h"
#include "Character/EncCharacterStateComponent.h"
#include "Items/Weapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
AEncCharacter::AEncCharacter(const FObjectInitializer& ObjectInitializer/* = FObjectInitializer::Get()*/)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEncCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SPRINTARM"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	CharacterState = CreateDefaultSubobject<UEncCharacterStateComponent>(TEXT("CHARACTERSTATE"));
	
	IsAttacking = false;
	CanSaveAttack = false;
	bInputAttack = false;
	CurrentCombo = 0;
	MaxComboCount = 2;
	AttackSpeed = 1.25f;
	SavedInput = FVector::ZeroVector;
	bRagdoll = false;

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

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("EncCharacter"));

	static ConstructorHelpers::FClassFinder<AWeapon> WEAPON(TEXT("/Game/Encounters/Items/BP_Sword.BP_Sword_C"));
	if (WEAPON.Succeeded())
	{
		DefaultWeaponClass = WEAPON.Class;
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

#if ENABLE_DRAW_DEBUG
	if (CurWeapon != nullptr && CurWeapon->IsShowAttackBox())
	{
		CurWeapon->DrawAttackBox();
	}
#endif
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
	PlayerInputComponent->BindAction(TEXT("Ragdoll"), EInputEvent::IE_Pressed, this, &AEncCharacter::StartRagdoll);
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

	CharacterState->OnHpIsZero.AddUObject(this, &AEncCharacter::Dead);

	if (CanSetWeapon())
	{
		SetWeapon(GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass));
	}
}

float AEncCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterState->SetDamage(FinalDamage);	
	return FinalDamage;
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

bool AEncCharacter::IsRagdoll() const
{
	return bRagdoll;
}

bool AEncCharacter::CanSetWeapon() const
{
	return (CurWeapon == nullptr);
}

void AEncCharacter::SetWeapon(AWeapon* Weapon)
{
	return_if(Weapon == nullptr);

	Weapon->SetOwner(this);
	Weapon->AttachToComponent(GetMesh(), 
		FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName(TEXT("hand_rSocket")));
	Weapon->SetActorRelativeRotation(Weapon->GetAttachRotator());

	CurWeapon = Weapon;
}

AWeapon* AEncCharacter::GetCurrentWeapon() const
{
	return CurWeapon;
}

float AEncCharacter::GetAttackDamage() const
{
	if (CurWeapon == nullptr)
		return 5.0f;

	return CurWeapon->GetAttackDamage();
}

void AEncCharacter::GiveAttackDamage(TWeakObjectPtr<AActor>& TargetPtr)
{
	if (!TargetPtr.IsValid())
		return;

	FDamageEvent DamageEvent;
	TargetPtr->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
}

void AEncCharacter::StartRagdoll()
{
	if (bRagdoll)
		return;

	EncCharacterMovement->SetMovementMode(EMovementMode::MOVE_None);	
	bRagdoll = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	USkeletalMeshComponent* SkMesh = GetMesh();
	SkMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SkMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkMesh->SetAllBodiesBelowSimulatePhysics(FName(TEXT("pelvis")), true, true);

	EncAnim->StopAllMontages(0.2f);
}

void AEncCharacter::MoveForward(float NewAxisValue)
{
	if (IsAttacking || IsRolling() || bRagdoll)
	{
		SavedInput.X = NewAxisValue;
		return;
	}

	AddMovementInput(FRotationMatrix(FRotator(0.0f, GetControlRotation().Yaw, 0.0f)).GetUnitAxis(EAxis::X), NewAxisValue);
}

void AEncCharacter::MoveRight(float NewAxisValue)
{
	if (IsAttacking || IsRolling() || bRagdoll)
	{
		SavedInput.Y = NewAxisValue;
		return;
	}

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
	if (CanSaveAttack)
		return;

	UEncCharacterMovementComponent* CharMovement = GetEncCharacterMovement();
	if (!CharMovement->CanRolling())
		return;

	FVector DirToMove = FVector::ZeroVector;
	if (IsAttacking)
	{
		DirToMove = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).RotateVector(SavedInput);
	}
	else
	{
		DirToMove = GetLastMovementInputVector();
	}
	
	if (DirToMove.IsNearlyZero())
		return;

	SetActorRotation(DirToMove.Rotation(), ETeleportType::TeleportPhysics);

	DirToMove.Normalize();
	CharMovement->Roll(DirToMove);

	if (IsAttacking)
	{
		EncAnim->StopAttackMontage();
	}
}

void AEncCharacter::Attack()
{
	if (IsRolling() || IsFalling() || bRagdoll)
		return;

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

		EncAnim->PlayAttackMontage(AttackSpeed);
		EncAnim->JumpToAttackMontageSection(CurrentCombo);		
	}	
}

void AEncCharacter::Dead()
{
	StartRagdoll();
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
		if (!SavedInput.IsNearlyZero())
		{
			FVector DirVec = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).RotateVector(SavedInput);
			SetActorRotation(DirVec.Rotation(), ETeleportType::TeleportPhysics);
		}
	}
}
