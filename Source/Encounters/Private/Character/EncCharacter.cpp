// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacter.h"
#include "Character/EncAnimInstance.h"
#include "Character/EncCharacterMovementComponent.h"
#include "Character/EncCharacterStateComponent.h"
#include "Items/Equipment.h"
#include "Items/Weapon.h"
#include "Items/Shield.h"
#include "DrawDebugHelpers.h"

AEncCharacter::AEncCharacter(const FObjectInitializer& ObjectInitializer/* = FObjectInitializer::Get()*/)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEncCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterState = CreateDefaultSubobject<UEncCharacterStateComponent>(TEXT("CHARACTERSTATE"));

	MaxComboCount = 2;
	AttackSpeed = 1.25f;
	RollingSpeed = 2.5f;
	RollingVelocityRate = 1.5f;
	DefenseSpeed = 2.0f;
	bShowAttackBox = false;
	bShowAttackBoxInAttack = false;
	bShowGaurdAngle = false;
	bShowGaurdSituation = false;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionProfileName(TEXT("EncCharacter"));

	UCharacterMovementComponent* CharMovementComp = GetCharacterMovement();
	CharMovementComp->bOrientRotationToMovement = true;
	CharMovementComp->bUseControllerDesiredRotation = false;
	CharMovementComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);

	USkeletalMeshComponent* SkeletalMeshComp = GetMesh();
	SkeletalMeshComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -88.0f), FRotator(0.0f, -90.0f, 0.0f));

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

	static ConstructorHelpers::FClassFinder<AWeapon> WEAPON(TEXT("/Game/Encounters/Items/BP_Sword.BP_Sword_C"));
	if (WEAPON.Succeeded())
	{
		DefaultWeaponClass = WEAPON.Class;
	}

	static ConstructorHelpers::FClassFinder<AShield> SHIELD(TEXT("/Game/Encounters/Items/BP_Shield.BP_Shield_C"));
	if (SHIELD.Succeeded())
	{
		DefaultShieldClass = SHIELD.Class;
	}
}

void AEncCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurWeapon != nullptr && bShowAttackBox)
	{
		CurWeapon->DrawAttackBox();
	}
	if (CurShield != nullptr && bShowGaurdAngle)
	{
		CurShield->DrawGaurdAngle();
	}
}

void AEncCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EncAnim = Cast<UEncAnimInstance>(GetMesh()->GetAnimInstance());
	if (EncAnim != nullptr)
	{
		EncAnim->OnMontageEnded.AddDynamic(this, &AEncCharacter::OnAttackMontageEnded);
		EncAnim->OnMontageEnded.AddDynamic(this, &AEncCharacter::OnRollingMontageEnded);
		EncAnim->OnComboEnable.AddUObject(this, &AEncCharacter::OnComboEnable);
		EncAnim->OnComboCheck.AddUObject(this, &AEncCharacter::OnComboCheck);
		EncAnim->OnBeginGaurd.AddUObject(this, &AEncCharacter::OnBeginGaurd);

		EncAnim->SetDefenseSpeed(DefenseSpeed);
	}

	CharacterState->OnHpIsZero.AddUObject(this, &AEncCharacter::Dead);

	if (CanSetWeapon())
	{
		SetWeapon(GetWorld()->SpawnActor<AWeapon>(DefaultWeaponClass));
	}

	if (CanSetShield())
	{
		SetShield(GetWorld()->SpawnActor<AShield>(DefaultShieldClass));
	}
}

float AEncCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanGaurd(DamageCauser))
	{
		if (bShowGaurdSituation)
		{
			DrawDebugGaurdSituation(DamageCauser);
		}
		
		return 0.0f;
	}		

	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	CharacterState->SetDamage(FinalDamage);	
	return FinalDamage;
}

bool AEncCharacter::IsRolling() const
{
	return bRolling;
}

bool AEncCharacter::IsFalling() const
{
	return GetCharacterMovement()->IsFalling();
}

bool AEncCharacter::IsRagdoll() const
{
	return bRagdoll;
}

bool AEncCharacter::IsDefending() const
{
	return bDefense;
}

bool AEncCharacter::CanSetWeapon() const
{
	return (CurWeapon == nullptr);
}

void AEncCharacter::SetWeapon(AWeapon* Weapon)
{
	static FName SocketName(TEXT("hand_rSocket"));
	SetEquipment(Weapon, SocketName);

	CurWeapon = Weapon;
}

AWeapon* AEncCharacter::GetCurrentWeapon() const
{
	return CurWeapon;
}

bool AEncCharacter::CanSetShield() const
{
	return (CurShield == nullptr);
}

void AEncCharacter::SetShield(AShield* Shield)
{
	static FName SocketName(TEXT("lowerarm_twist_lSocket"));
	SetEquipment(Shield, SocketName);

	CurShield = Shield;
}

AShield* AEncCharacter::GetCurrentShield() const
{
	return nullptr;
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

bool AEncCharacter::CanGaurd(AActor* Attacker)
{
	return_if(Attacker == nullptr, true);

	if (CurShield == nullptr)
		return false;

	FVector AttackerDir = Attacker->GetActorLocation() - GetActorLocation();
	AttackerDir.Z = 0.0f;
	AttackerDir.Normalize();

	float Cosine = FVector::DotProduct(GetActorForwardVector(), AttackerDir);
	
	return (CurShield->GetGaurdAngleCosine() <= Cosine);
}

float AEncCharacter::GetRollingSpeed() const
{
	return RollingSpeed;
}

void AEncCharacter::StartRagdoll()
{
	if (bRagdoll)
		return;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	
	bRagdoll = true;

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	USkeletalMeshComponent* SkMesh = GetMesh();
	SkMesh->SetCollisionObjectType(ECollisionChannel::ECC_PhysicsBody);
	SkMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkMesh->SetAllBodiesBelowSimulatePhysics(FName(TEXT("pelvis")), true, true);

	if (EncAnim != nullptr)
	{
		EncAnim->StopAllMontages(0.2f);
	}
}

float AEncCharacter::GetCurrentRootMotionVelocityRate() const
{
	return CurrentRootMotionVelocityRate;
}

bool AEncCharacter::IsShowAttackBoxInAttack() const
{
#if ENABLE_DRAW_DEBUG
	return bShowAttackBoxInAttack;
#else
	return false;
#endif
}

void AEncCharacter::Roll()
{
	if (bRolling || CanSaveAttack || IsFalling())
		return;

	FVector DirToMove(FVector::ZeroVector);
	if (bAttacking)
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

	CurrentRootMotionVelocityRate = RollingVelocityRate;
	if (EncAnim != nullptr)
	{
		EncAnim->PlayRollingMontage(RollingSpeed);
	}

	bRolling = true;
}

void AEncCharacter::Attack()
{
	if (bRolling || IsFalling() || bRagdoll)
		return;

	if (bAttacking)
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
		bAttacking = true;

		if (EncAnim != nullptr)
		{
			EncAnim->PlayAttackMontage(AttackSpeed);
			EncAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	}
}

void AEncCharacter::Dead()
{
	StartRagdoll();
	DefenseDown();
}

void AEncCharacter::DefenseUp()
{
	if (bRagdoll)
		return;

	bDefense = true;
}

void AEncCharacter::DefenseDown()
{
	bDefense = false;
	bGaurding = false;
}

void AEncCharacter::DrawDebugGaurdSituation(AActor* DamageCauser)
{
#if ENABLE_DRAW_DEBUG
	AEncCharacter* Attacker = Cast<AEncCharacter>(DamageCauser);
	if (Attacker != nullptr)
	{
		AWeapon* Weapon = Attacker->GetCurrentWeapon();
		if (Weapon != nullptr)
		{
			Weapon->DrawAttackBox(FColor::Red);
		}
	}
	if (CurShield != nullptr)
	{
		CurShield->DrawGaurdAngle(FColor::Blue);
	}

	FVector MyPos = GetActorLocation();
	FVector AttackerPos = MyPos;
	if (Attacker != nullptr)
	{
		AttackerPos = Attacker->GetActorLocation();
	}

	DrawDebugPoint(GetWorld(), MyPos, 10.0f, FColor::Green, false, 5.0f);
	DrawDebugPoint(GetWorld(), AttackerPos, 10.0f, FColor::Green, false, 5.0f);
	DrawDebugLine(GetWorld(), MyPos, AttackerPos, FColor::Green, false, 5.0f);
#endif // ENABLE_DRAW_DEBUG
}

void AEncCharacter::SetEquipment(AEquipment* Equipment, const FName& SocketName)
{
	return_if(Equipment == nullptr);

	Equipment->SetOwner(this);
	Equipment->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, SocketName);
	Equipment->SetActorRelativeRotation(Equipment->GetAttachRotator());
}

void AEncCharacter::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (EncAnim != nullptr && !EncAnim->IsAttackMontage(Montage))
		return;

	CurrentCombo = 0;
	bInputAttack = false;
	bAttacking = false;
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

		if (EncAnim != nullptr)
		{
			EncAnim->JumpToAttackMontageSection(CurrentCombo);
		}

		if (!SavedInput.IsNearlyZero())
		{
			FVector DirVec = FRotator(0.0f, GetControlRotation().Yaw, 0.0f).RotateVector(SavedInput);
			SetActorRotation(DirVec.Rotation(), ETeleportType::TeleportPhysics);
		}
	}
}

void AEncCharacter::OnRollingMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (EncAnim != nullptr && !EncAnim->IsRollingMontage(Montage))
		return;

	CurrentRootMotionVelocityRate = 1.0f;
	bRolling = false;
}

void AEncCharacter::OnBeginGaurd()
{
	bGaurding = true;
}
