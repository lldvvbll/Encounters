// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "DrawDebugHelpers.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	RootComponent = SkMeshComp;

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	AttachRotator = FRotator::ZeroRotator;
	AttackBoxHalfExtent = FVector::ZeroVector;
	bShowAttackBox = false;
	bShowAttackBoxInAttack = false;
	DebugAttackBoxLifeTime = 0.5f;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRotator AWeapon::GetAttachRotator() const
{
	return AttachRotator;
}

FVector AWeapon::GetAttackBoxSocketPos() const
{
	static FName AttackBoxSocketName(TEXT("attackTrace"));
	return SkMeshComp->GetSocketLocation(AttackBoxSocketName);
}

FVector AWeapon::GetAttackBoxHalfExtent() const
{
	return AttackBoxHalfExtent;
}

bool AWeapon::IsShowAttackBox() const
{
	return bShowAttackBox;
}

bool AWeapon::IsShowAttackBoxInAttack() const
{
	return bShowAttackBoxInAttack;
}

void AWeapon::DrawAttackBox() const
{
	FVector Pos = GetAttackBoxSocketPos();
	FVector Extent = AttackBoxHalfExtent * 2.0f * GetActorScale();
	FQuat Quat = GetActorRotation().Quaternion();
	DrawDebugBox(GetWorld(), Pos, Extent, Quat, FColor::Red, false, DebugAttackBoxLifeTime);
}

