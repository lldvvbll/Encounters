// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncCharacter.generated.h"

class UEncAnimInstance;
class AWeapon;
class UEncCharacterStateComponent;

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	//AEncCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	AEncCharacter();

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

	float GetAttackDamage() const;
	void GiveAttackDamage(TWeakObjectPtr<AActor>& Target);

	float GetRollingSpeed() const;
	float GetRollingForceScale() const;

	void StartRagdoll();

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);

	void Roll();
	void Attack();
	void Dead();
	void DefenseUp();
	void DefenseDown();

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

private:
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY()
	UEncAnimInstance* EncAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, Meta = (AllowPrivateAccess = true))
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleInstanceOnly, Category = Weapon, Meta = (AllowPrivateAccess = true))
	AWeapon* CurWeapon;

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
	float RollingForceScale;

	UPROPERTY(VisibleInstanceOnly, Category = Ragdoll, Meta = (AllowPrivateAccess = true))
	bool bRagdoll;

	UPROPERTY(VisibleInstanceOnly, Category = Defense, Meta = (AllowPrivateAccess = true))
	bool bDefense;

	UPROPERTY(EditAnywhere, Category = Defense, Meta = (AllowPrivateAccess = true))
	float DefenseSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Defense, Meta = (AllowPrivateAccess = true))
	bool bGaurding;
};
