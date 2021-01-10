// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class ENCOUNTERS_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FRotator GetAttachRotator() const;
	FVector GetAttackBoxSocketPos() const;
	FVector GetAttackBoxHalfExtent() const;

	bool IsShowAttackBox() const;
	bool IsShowAttackBoxInAttack() const;
	void DrawAttackBox() const;

	float GetAttackDamage() const;

private:
	UPROPERTY(VisibleAnywhere, Category = Mesh, Meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkMeshComp;

	UPROPERTY(EditDefaultsOnly, Category = Transform, Meta = (AllowPrivateAccess = true))
	FRotator AttachRotator;

	UPROPERTY(EditDefaultsOnly, Category = AttackTrace, Meta = (AllowPrivateAccess = true))
	FVector AttackBoxHalfExtent;

	UPROPERTY(EditDefaultsOnly, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowAttackBox;

	UPROPERTY(EditDefaultsOnly, Category = Debug, Meta = (AllowPrivateAccess = true))
	bool bShowAttackBoxInAttack;

	UPROPERTY(EditDefaultsOnly, Category = Debug, Meta = (AllowPrivateAccess = true))
	float DebugAttackBoxLifeTime;

	UPROPERTY(EditAnywhere, Category = Damage, Meta = (AllowPrivateAccess = true))
	float DefaultDamage;
};
