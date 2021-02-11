// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/EncCharacter.h"
#include "Character/EncAnimInstance.h"
#include "Character/EncCharacterMovementComponent.h"
#include "Character/EncCharacterStateComponent.h"
#include "Character/InventoryComponent.h"
#include "Items/Actors/Equipment.h"
#include "Items/Actors/Weapon.h"
#include "Items/Actors/Shield.h"
#include "Items/Actors/Armor.h"
#include "Items/DataAssets/WeaponDataAsset.h"
#include "Items/DataAssets/ShieldDataAsset.h"
#include "Items/DataAssets/ArmorDataAsset.h"
#include "Items/EncItem.h"
#include "EncStructures.h"
#include "DrawDebugHelpers.h"

AEncCharacter::AEncCharacter(const FObjectInitializer& ObjectInitializer/* = FObjectInitializer::Get()*/)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UEncCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterState = CreateDefaultSubobject<UEncCharacterStateComponent>(TEXT("CHARACTERSTATE"));
	Inventory = CreateDefaultSubobject<UInventoryComponent>(TEXT("INVENTORY"));

	MaxComboCount = 2;
	LockOnDistanceMax = 800.0f;
	LockOnDistanceMaxSquared = LockOnDistanceMax * LockOnDistanceMax;
	
	bShowAttackBox = false;
	bShowAttackBoxInAttack = false;
	bShowGuardAngle = false;
	bShowGuardSituation = true;

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
}

void AEncCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurWeapon != nullptr && bShowAttackBox)
	{
		CurWeapon->DrawAttackBox();
	}
	if (CurShield != nullptr && bShowGuardAngle)
	{
		CurShield->DrawGuardAngle();
	}
}

void AEncCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	EncAnim = Cast<UEncAnimInstance>(GetMesh()->GetAnimInstance());
	if (EncAnim != nullptr)
	{
		EncAnim->OnMontageStarted.AddDynamic(this, &AEncCharacter::OnMontageStarted);
		EncAnim->OnMontageEnded.AddDynamic(this, &AEncCharacter::OnMontageEnded);
		EncAnim->OnComboEnable.AddUObject(this, &AEncCharacter::OnComboEnable);
		EncAnim->OnComboCheck.AddUObject(this, &AEncCharacter::OnComboCheck);
		EncAnim->OnBeginAvoidance.AddUObject(this, &AEncCharacter::OnBeginAvoidance);
		EncAnim->OnEndAvoidance.AddUObject(this, &AEncCharacter::OnEndAvoidance);
		EncAnim->OnGuardUp.AddUObject(this, &AEncCharacter::OnGuardUp);
	}

	CharacterState->OnHpIsZero.AddUObject(this, &AEncCharacter::Dead);
	Inventory->OnAddItem.AddUObject(this, &AEncCharacter::OnAddItemToInventory);
}

float AEncCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (CanGuardByShield(DamageCauser))
	{
		if (bShowGuardSituation)
		{
			DrawDebugGuardSituation(DamageCauser);
		}
		
		if (CurShield != nullptr)
		{
			float UseStamina = CurShield->GetUseStaminaOnGuard();
			if (UseStamina >= 0.0f && CharacterState->GetStamina() >= UseStamina)
			{
				CharacterState->ModifyStamina(-UseStamina);
				CharacterState->SetStaminaRecovery(false);
				bShovedOnBlocking = true;

				if (EncAnim != nullptr)
				{
					EncAnim->PlayShovedOnBlockingMontage(1.0f);
				}

				if (DamageCauser != nullptr)
				{
					FVector Dir = GetActorLocation() - DamageCauser->GetActorLocation();
					Dir.Normalize();

					LaunchCharacter(Dir * 500.0f, false, false);
				}

				DamageAmount = FMath::Max(0.0f, DamageAmount * (1.0f - CurShield->GetDamageReduction()));
			}
		}				
	}		

	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (FinalDamage > KINDA_SMALL_NUMBER)
	{
		CharacterState->ModifyHP(-FinalDamage);
		bFlinching = true;

		if (EncAnim != nullptr)
		{
			EncAnim->PlayFlinchMontage(1.0f);
		}

		if (DamageCauser != nullptr)
		{
			FVector Dir = GetActorLocation() - DamageCauser->GetActorLocation();
			Dir.Normalize();

			LaunchCharacter(Dir * 500.0f, false, false);
		}
	}
	else
	{
		if (!CanBeDamaged())
		{
			auto Capsule = GetCapsuleComponent();
			DrawDebugCapsule(GetWorld(), Capsule->GetComponentLocation(), Capsule->GetScaledCapsuleHalfHeight(), Capsule->GetScaledCapsuleRadius(),
				Capsule->GetComponentQuat(), FColor::Red, false, 1.0f);
		}
	}

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

void AEncCharacter::SetWeapon(UWeaponDataAsset* DataAsset)
{
	return_if(DataAsset == nullptr);

	auto Weapon = GetWorld()->SpawnActor<AWeapon>(DataAsset->ItemActorClass);
	return_if(Weapon == nullptr);

	Weapon->SetItemDataAsset(DataAsset);
	SetWeapon(Weapon);
}

AWeapon* AEncCharacter::GetCurrentWeapon() const
{
	return CurWeapon;
}

void AEncCharacter::RemoveWeapon()
{
	if (CurWeapon == nullptr)
		return;

	GetWorld()->DestroyActor(CurWeapon);
	CurWeapon = nullptr;
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

	if (EncAnim != nullptr)
	{
		float GuardSpeed = (CurShield != nullptr) ? CurShield->GetGuardSpeed() : 0.0f;
		EncAnim->SetGuardSpeed(GuardSpeed);
	}
}

void AEncCharacter::SetShield(UShieldDataAsset* DataAsset)
{
	return_if(DataAsset == nullptr);

	auto Shield = GetWorld()->SpawnActor<AShield>(DataAsset->ItemActorClass);
	return_if(Shield == nullptr);

	Shield->SetItemDataAsset(DataAsset);
	SetShield(Shield);
}

AShield* AEncCharacter::GetCurrentShield() const
{
	return CurShield;
}

void AEncCharacter::RemoveShield()
{
	if (CurShield == nullptr)
		return;

	GetWorld()->DestroyActor(CurShield);
	CurShield = nullptr;

	if (EncAnim != nullptr)
	{
		EncAnim->SetGuardSpeed(0.0f);
	}
}

bool AEncCharacter::CanSetArmor() const
{
	return (CurArmor == nullptr);
}

void AEncCharacter::SetArmor(AArmor* Armor)
{
	static FName SocketName(TEXT("body_Socket"));
	SetEquipment(Armor, SocketName);

	CurArmor = Armor;
}

void AEncCharacter::SetArmor(UArmorDataAsset* DataAsset)
{
	return_if(DataAsset == nullptr);

	auto Armor = GetWorld()->SpawnActor<AArmor>(DataAsset->ItemActorClass);
	return_if(Armor == nullptr);

	Armor->SetItemDataAsset(DataAsset);
	SetArmor(Armor);
}

AArmor* AEncCharacter::GetCurrentArmor() const
{
	return CurArmor;
}

void AEncCharacter::RemoveArmor()
{
	if (CurArmor == nullptr)
		return;

	GetWorld()->DestroyActor(CurArmor);
	CurArmor = nullptr;
}

bool AEncCharacter::Attack()
{
	if (bRolling || IsFalling() || bRagdoll || bShovedOnBlocking)
		return false;

	if (CurWeapon == nullptr)
		return false;

	float UseStamina = CurWeapon->GetUseStaminaOnAttack();
	if (UseStamina < 0.0f)
		return false;

	if (CharacterState->GetStamina() < UseStamina)
		return false;
	
	if (bAttacking)
	{
		if (bCanSaveAttack)
		{
			bInputAttack = true;
		}
	}
	else
	{
		CurrentCombo = 1;
		bInputAttack = false;
		bAttacking = true;

		CharacterState->ModifyStamina(-UseStamina);

		if (EncAnim != nullptr)
		{
			EncAnim->PlayAttackMontage(CurWeapon->GetAttackSpeed());
			EncAnim->JumpToAttackMontageSection(CurrentCombo);
		}
	}

	return true;
}

bool AEncCharacter::IsAttacking() const
{
	return bAttacking;
}

bool AEncCharacter::CanSaveAttack() const
{
	return bCanSaveAttack;
}

float AEncCharacter::GetAttackDamage() const
{
	float AttackPower = CharacterState->GetAttackPower();

	if (CurWeapon == nullptr)
		return AttackPower;

	return AttackPower + CurWeapon->GetAttackDamage();
}

float AEncCharacter::GiveAttackDamage(TWeakObjectPtr<AActor>& TargetPtr)
{
	if (!TargetPtr.IsValid())
		return 0.0f;

	FDamageEvent DamageEvent;
	return TargetPtr->TakeDamage(GetAttackDamage(), DamageEvent, GetController(), this);
}

void AEncCharacter::Guard()
{
	if (bRagdoll)
		return;

	bGuarding = true;
	CharacterState->SetStaminaRecoverySpeed(2.5f);
}

void AEncCharacter::GuardDown()
{
	bGuarding = false;
	bGuardUp = false;
	CharacterState->SetStaminaRecoverySpeed(5.0f);
}

bool AEncCharacter::CanGuardByShield(AActor* Attacker)
{
	return_if(Attacker == nullptr, true);

	if (CurShield == nullptr)
		return false;

	if (!bGuardUp)
		return false;

	FVector AttackerDir = Attacker->GetActorLocation() - GetActorLocation();
	AttackerDir.Normalize();

	float Cosine = FVector::DotProduct(GetActorForwardVector(), AttackerDir);
	
	return (CurShield->GetGuardAngleCosine() <= Cosine);
}

bool AEncCharacter::IsGuarding() const
{
	return bGuarding;
}

bool AEncCharacter::IsShovedOnBlocking() const
{
	return bShovedOnBlocking;
}

void AEncCharacter::Roll()
{
	if (bRolling || bCanSaveAttack || IsFalling() || bShovedOnBlocking)
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

	float UseStamina = (CurArmor != nullptr) ? CurArmor->GetUseStaminaOnRolling() : 0.0f;
	if (UseStamina < 0.0f)
		return;

	if (CharacterState->GetStamina() < UseStamina)
		return;

	CharacterState->ModifyStamina(-UseStamina);

	SetActorRotation(DirToMove.Rotation(), ETeleportType::TeleportPhysics);

	if (EncAnim != nullptr)
	{
		CurrentRootMotionVelocityRate = CharacterState->GetRollingVelocityRate();
		EncAnim->PlayRollingMontage(CharacterState->GetRolligSpeed());
	}

	bRolling = true;
}

void AEncCharacter::Dead()
{
	bDead = true;

	GuardDown();
	SetCanBeDamaged(false);
	CharacterState->SetStaminaRecovery(false);

	StartRagdoll();
}

bool AEncCharacter::IsDead() const
{
	return bDead;
}

void AEncCharacter::StartRagdoll()
{
	if (bRagdoll)
		return;

	bRagdoll = true;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);	
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

UEncCharacterStateComponent* AEncCharacter::GetCharacterStateComponent() const
{
	return CharacterState;
}

bool AEncCharacter::IsShowAttackBoxInAttack() const
{
#if ENABLE_DRAW_DEBUG
	return bShowAttackBoxInAttack;
#else
	return false;
#endif
}

void AEncCharacter::DrawDebugGuardSituation(AActor* DamageCauser)
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
		CurShield->DrawGuardAngle(FColor::Blue);
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
	Equipment->SetActorRelativeLocation(Equipment->GetAttachOffset());
	Equipment->SetActorRelativeRotation(Equipment->GetAttachRotator());
}

void AEncCharacter::OnMontageStarted(UAnimMontage* Montage)
{
	if (EncAnim != nullptr)
	{
		if (!EncAnim->IsShovedOnBlockingMontage(Montage))
		{
			bGuardUp = false;
		}
	}	

	CharacterState->SetStaminaRecovery(false);
}

void AEncCharacter::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (EncAnim != nullptr)
	{
		if (EncAnim->IsAttackMontage(Montage))
		{
			CurrentCombo = 0;
			bInputAttack = false;
			bAttacking = false;
		}
		else if (EncAnim->IsRollingMontage(Montage))
		{
			CurrentRootMotionVelocityRate = 1.0f;
			bRolling = false;
			SetCanBeDamaged(true);
		}
		else if (EncAnim->IsShovedOnBlockingMontage(Montage))
		{
			bShovedOnBlocking = false;
		}
		else if (EncAnim->IsFlinchMontage(Montage))
		{
			bFlinching = false;
		}
	}

	CharacterState->SetStaminaRecovery(true);
}

void AEncCharacter::OnComboEnable()
{
	bCanSaveAttack = true;
}

void AEncCharacter::OnComboCheck()
{
	bCanSaveAttack = false;

	if (!bInputAttack)
		return;

	bInputAttack = false;

	if (CurWeapon == nullptr)
		return;

	float UseStamina = CurWeapon->GetUseStaminaOnAttack();
	if (UseStamina < 0.0f)
		return;

	if (CharacterState->GetStamina() < UseStamina)
		return;

	++CurrentCombo;
	if (CurrentCombo > MaxComboCount)
	{
		CurrentCombo = 1;
	}

	CharacterState->ModifyStamina(-UseStamina);
	CharacterState->SetStaminaRecovery(false);

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

void AEncCharacter::OnBeginAvoidance()
{
	SetCanBeDamaged(false);
}

void AEncCharacter::OnEndAvoidance()
{
	SetCanBeDamaged(true);
}

void AEncCharacter::OnGuardUp()
{
	bGuardUp = true;
}

void AEncCharacter::OnAddItemToInventory(EPocketType PocketType, UEncItem* NewItem)
{
	return_if(NewItem == nullptr);

	switch (PocketType)
	{
	case EPocketType::Weapon:
		{
			SetWeapon(Cast<UWeaponDataAsset>(NewItem->GetDataAsset()));
		}		
		break;
	case EPocketType::Shield:
		{
			SetShield(Cast<UShieldDataAsset>(NewItem->GetDataAsset()));
		}
		break;
	case EPocketType::Armor:
		{
			SetArmor(Cast<UArmorDataAsset>(NewItem->GetDataAsset()));
		}
		break;
	default:
		break;
	}
}

void AEncCharacter::OnRemoveItemFromInventory(EPocketType PocketType, UEncItem* RemovedItem)
{
	switch (PocketType)
	{
	case EPocketType::Weapon:
		{
			RemoveWeapon();
		}
		break;
	case EPocketType::Shield:
		{
			RemoveShield();
		}
		break;
	case EPocketType::Armor:
		{
			RemoveArmor();
		}
		break;
	default:
		break;
	}
}