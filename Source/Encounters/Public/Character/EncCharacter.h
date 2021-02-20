// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncStructures.h"
#include "EncCharacter.generated.h"

class UEncAnimInstance;
class AEquipment;
class AWeapon;
class AShield;
class AArmor;
class UEncCharacterStateComponent;
class UWidgetComponent;
class UInventoryComponent;
class UEncItem;
class UWeaponDataAsset;
class UShieldDataAsset;
class UArmorDataAsset;

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEncCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	bool IsRolling() const;
	bool IsFalling() const;
	bool IsRagdoll() const;

	bool CanSetWeapon() const;
	void SetWeapon(AWeapon* Weapon);
	void SetWeapon(UWeaponDataAsset* DataAsset);
	AWeapon* GetCurrentWeapon() const;
	void RemoveWeapon();

	bool CanSetShield() const;
	void SetShield(AShield* Shield);
	void SetShield(UShieldDataAsset* DataAsset);
	AShield* GetCurrentShield() const;
	void RemoveShield();

	bool CanSetArmor() const;
	void SetArmor(AArmor* Armor);
	void SetArmor(UArmorDataAsset* DataAsset);
	AArmor* GetCurrentArmor() const;
	void RemoveArmor();

	bool Attack();
	bool IsAttacking() const;
	bool CanSaveAttack() const;
	float GetAttackDamage() const;
	virtual float GiveAttackDamage(TWeakObjectPtr<AActor>& Target);
	void SetSavedInput(const FVector& Input);
	virtual void RotateBySavedInput();
	float GetStaminaForAttack() const;

	void Guard();
	void GuardDown();
	bool CanGuardByShield(AActor* Attacker);
	bool IsGuarding() const;
	bool IsShovedOnBlocking() const;

	void Roll();

	virtual void Dead();
	bool IsDead() const;
	void StartRagdoll();

	virtual void LockOn() {}
	virtual void ReleaseLockOn() {}
	virtual bool IsLockOnTarget() const { return false; }
	virtual TWeakObjectPtr<AEncCharacter> FindLockOnTarget() const { return TWeakObjectPtr<AEncCharacter>(); }

	float GetCurrentStamina() const;
	float GetCurrentStaminaRatio() const;
	float GetCurrentRootMotionVelocityRate() const;

	UEncCharacterStateComponent* GetCharacterStateComponent() const;

	void DrawDebugGuardSituation(AActor* DamageCauser);

protected:
	void SetEquipment(AEquipment* Equipment, const FName& SocketName);

	UFUNCTION()
	void OnMontageStarted(UAnimMontage* Montage);

	UFUNCTION()
	void OnMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	UFUNCTION()
	void OnComboEnable();

	UFUNCTION()
	void OnComboCheck();

	UFUNCTION()
	void OnBeginAvoidance();

	UFUNCTION()
	void OnEndAvoidance();

	UFUNCTION()
	void OnGuardUp();

	UFUNCTION()
	void OnAddItemToInventory(EPocketType PocketType, UEncItem* NewItem);

	UFUNCTION()
	void OnRemoveItemFromInventory(EPocketType PocketType, UEncItem* RemovedItem);

protected:
	UPROPERTY()
	UEncAnimInstance* EncAnim;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AWeapon* CurWeapon;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AShield* CurShield;

	UPROPERTY(VisibleInstanceOnly, Category = Equipment)
	AArmor* CurArmor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = State)
	UEncCharacterStateComponent* CharacterState;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory)
	UInventoryComponent* Inventory;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack)
	bool bAttacking;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack)
	bool bCanSaveAttack;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack)
	bool bInputAttack;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack)
	int32 CurrentCombo;

	UPROPERTY(VisibleInstanceOnly, Category = Attack)
	int32 MaxComboCount;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Attack)
	FVector SavedInput;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Rolling)
	bool bRolling;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Ragdoll)
	bool bDead;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Ragdoll)
	bool bRagdoll;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Guard)
	bool bGuarding;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Guard)
	bool bGuardUp;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Guard)
	bool bShovedOnBlocking;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = Guard)
	bool bFlinching;

	UPROPERTY(EditAnywhere, Category = LockOn)
	float LockOnDistanceMax;

	UPROPERTY(Transient)
	float LockOnDistanceMaxSquared;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = LockOn)
	TWeakObjectPtr<AEncCharacter> LockedOnTarget;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = LockOn)
	bool bLockOnTarget;

	UPROPERTY(Transient, VisibleInstanceOnly, Category = RootMotion)
	float CurrentRootMotionVelocityRate;

	UPROPERTY(Transient, EditAnywhere, Category = Debug)
	bool bShowGuardSituation;
};
