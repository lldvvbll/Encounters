// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Character/EncCharacter.h"
#include "EncStructures.h"
#include "PlayerCharacter.generated.h"

class UEncSaveGame;

USTRUCT()
struct FLockOnCandidate
{
	GENERATED_BODY()

	UPROPERTY()
	bool bFrontOfChar;

	UPROPERTY()
	bool bFrontOfCam;

	UPROPERTY()
	float DistanceSquared;

	UPROPERTY()
	TWeakObjectPtr<AEncCharacter> TargetPtr;
};

UCLASS()
class ENCOUNTERS_API APlayerCharacter : public AEncCharacter
{
	GENERATED_BODY()
	
public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void UnPossessed() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Dead() override;

	virtual void LockOn() override;
	virtual void ReleaseLockOn() override;
	virtual bool IsLockOnTarget() const override;
	virtual TWeakObjectPtr<AEncCharacter> FindLockOnTarget() const override;

	void InitCharacterData();
	void LoadCharacter(const UEncSaveGame* SaveGame);
	void SaveCharacter(UEncSaveGame* SaveGame);

protected:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	
	void OnAttackButtonPressed();

	FVector GetCameraRotationPivot() const;

	void OnPlayerStateChanged(EPlayerStateAttribute Attribute);

private:
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	FDelegateHandle OnPlayerStateChangedDelegetHandle;
};
