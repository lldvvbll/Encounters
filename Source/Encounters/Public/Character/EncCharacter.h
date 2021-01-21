// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncCharacter.generated.h"

class UEncAnimInstance;
class AEquipment;
class AWeapon;
class AShield;
class UEncCharacterStateComponent;

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEncCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool IsRolling() const;
	bool IsFalling() const;
	bool IsRagdoll() const;
	bool IsDefending() const;

	bool CanSetWeapon() const;
	void SetWeapon(AWeapon* Weapon);
	AWeapon* GetCurrentWeapon() const;

	bool CanSetShield() const;
	void SetShield(AShield* Shield);
	AShield* GetCurrentShield() const;

	float GetAttackDamage() const;
	void GiveAttackDamage(TWeakObjectPtr<AActor>& Target);

	bool CanGaurd(AActor* Attacker);

	float GetRollingSpeed() const;

	void StartRagdoll();

	float GetCurrentRootMotionVelocityRate() const;

	bool IsShowAttackBoxInAttack() const;

	void Roll();
	void Attack();
	void Dead();
	void DefenseUp();
	void DefenseDown();

	void DrawDebugGaurdSituation(AActor* DamageCauser);

protected:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void SetEquipment(AEquipment* Equipment, const FName& SocketName);

	UFUNCTION()
	void OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnComboEnable();

	UFUNCTION()
	void OnComboCheck();

	UFUNCTION()
	void OnRollingMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnBeginGaurd();

protected:
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY()
	UEncAnimInstance* EncAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment, Meta = (AllowPrivateAccess = true))
	AWeapon* CurWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AShield> DefaultShieldClass;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment, Meta = (AllowPrivateAccess = true))
	AShield* CurShield;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State, Meta = (AllowPrivateAccess = true))
	UEncCharacterStateComponent* CharacterState;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bAttacking;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool CanSaveAttack;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	bool bInputAttack;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	int32 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = Attack, Meta = (AllowPrivateAccess = true))
	float AttackSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	FVector SavedInput;

	UPROPERTY(VisibleInstanceOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
	bool bRolling;

	UPROPERTY(VisibleInstanceOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
	float RollingSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Rolling, Meta = (AllowPrivateAccess = true))
	float RollingVelocityRate;

	UPROPERTY(VisibleInstanceOnly, Category = Ragdoll, Meta = (AllowPrivateAccess = true))
	bool bRagdoll;

	UPROPERTY(VisibleInstanceOnly, Category = Defense, Meta = (AllowPrivateAccess = true))
	bool bDefense;

	UPROPERTY(EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float DefenseSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Defense, Meta = (AllowPrivateAccess = true))
	bool bGaurding;

	UPROPERTY(EditAnywhere, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowAttackBox;

	UPROPERTY(EditAnywhere, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowAttackBoxInAttack;

	UPROPERTY(EditAnywhere, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowGaurdAngle;
	
	UPROPERTY(EditAnywhere, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowGaurdSituation;

	float CurrentRootMotionVelocityRate = 0.0f;
	float GaurdAngleCosine = 0.0f;
};
