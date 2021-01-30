// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncCharacter.generated.h"

class UEncAnimInstance;
class AEquipment;
class AWeapon;
class AShield;
class AArmor;
class UEncCharacterStateComponent;
class UWidgetComponent;

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEncCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void Tick(float DeltaTime) override;
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

	bool CanSetArmor() const;
	void SetArmor(AArmor* Armor);
	AArmor* GetCurrentArmor() const;

	void Attack();
	float GetAttackDamage() const;
	void GiveAttackDamage(TWeakObjectPtr<AActor>& Target);

	void DefenseUp();
	void DefenseDown();
	bool CanGaurd(AActor* Attacker);

	void Roll();

	virtual void Dead();
	bool IsDead() const;
	void StartRagdoll();

	virtual void LockOn() {}
	virtual void ReleaseLockOn() {}
	virtual bool IsLockOnTarget() const { return false; }
	virtual TWeakObjectPtr<AEncCharacter> FindLockOnTarget() const { return TWeakObjectPtr<AEncCharacter>(); }

	float GetCurrentRootMotionVelocityRate() const;

	UEncCharacterStateComponent* GetCharacterStateComponent() const;

	bool IsShowAttackBoxInAttack() const;
	void DrawDebugGaurdSituation(AActor* DamageCauser);

protected:
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
	UPROPERTY()
	UEncAnimInstance* EncAnim;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	TSubclassOf<AWeapon> DefaultWeaponClass;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AWeapon* CurWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	TSubclassOf<AShield> DefaultShieldClass;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AShield* CurShield;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Equipment)
	TSubclassOf<AArmor> DefaultArmorClass;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AArmor* CurArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	UEncCharacterStateComponent* CharacterState;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	bool bAttacking;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	bool CanSaveAttack;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	bool bInputAttack;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	int32 MaxComboCount;

	UPROPERTY(EditAnywhere, Category = Attack)
	float AttackSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	FVector SavedInput;

	UPROPERTY(VisibleInstanceOnly, Category = Rolling)
	bool bRolling;

	UPROPERTY(VisibleInstanceOnly, Category = Ragdoll)
	bool bDead;

	UPROPERTY(VisibleInstanceOnly, Category = Ragdoll)
	bool bRagdoll;

	UPROPERTY(VisibleInstanceOnly, Category = Defense)
	bool bDefense;

	UPROPERTY(EditAnywhere, Category = Defense)
	float DefenseSpeed;

	UPROPERTY(VisibleInstanceOnly, Category = Defense)
	bool bGaurding;

	UPROPERTY(VisibleInstanceOnly, Category = Defense)
	float GaurdAngleCosine;

	UPROPERTY(EditAnywhere, Category = LockOn)
	float LockOnDistanceMax;

	UPROPERTY()
	float LockOnDistanceMaxSquared;

	UPROPERTY(VisibleInstanceOnly, Category = LockOn)
	TWeakObjectPtr<AEncCharacter> LockedOnTarget;

	UPROPERTY(VisibleInstanceOnly, Category = LockOn)
	bool bLockOnTarget;

	UPROPERTY(VisibleInstanceOnly, Category = RootMotion)
	float CurrentRootMotionVelocityRate;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool bShowAttackBox;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool bShowAttackBoxInAttack;

	UPROPERTY(EditAnywhere, Category = Debug)
	bool bShowGaurdAngle;
	
	UPROPERTY(EditAnywhere, Category = Debug)
	bool bShowGaurdSituation;
};
