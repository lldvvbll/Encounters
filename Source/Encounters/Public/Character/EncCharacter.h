// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Character.h"
#include "EncCharacter.generated.h"

class UEncCharacterMovementComponent;

UCLASS()
class ENCOUNTERS_API AEncCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEncCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitializeComponents() override;

	UEncCharacterMovementComponent* GetEncCharacterMovement() const;

	bool IsRolling() const;
	bool IsFalling() const;

private:
	void MoveForward(float NewAxisValue);
	void MoveRight(float NewAxisValue);
	void LookUp(float NewAxisValue);
	void Turn(float NewAxisValue);
	void Rolling();

private:
	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = true))
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character, Meta = (AllowPrivateAccess = true))
	UEncCharacterMovementComponent* EncCharacterMovement;
};
