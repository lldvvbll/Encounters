// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncCharacter.generated.h"

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEncCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void Rolling();

	void BeginRolling(const FVector& Direction);
	void EndRolling();

private:
	UPROPERTY()
	USpringArmComponent* SpringArm;

	UPROPERTY()
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, Category = Rolling, Meta = (AllowPrivateAccess = true))
	float RollingDuration;

	UPROPERTY(EditAnywhere, Category = Rolling, Meta = (AllowPrivateAccess = true))
	float RollingForceScale;

	UPROPERTY(EditAnywhere, Category = Rolling, Meta = (AllowPrivateAccess = true))
	float RollingAfterDelay;

	bool bRolling = false;
	float RollingRemainTime = 0.0f;
	FVector RollingDirection = FVector::ZeroVector;
};
