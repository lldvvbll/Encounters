// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"
#include "DrawDebugHelpers.h"

AWeapon::AWeapon()
{
	DefaultDamage = 10.0f;
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

FVector AWeapon::GetAttackBoxSocketPos() const
{
	static FName AttackBoxSocketName(TEXT("attackTrace"));
	return SkMeshComp->GetSocketLocation(AttackBoxSocketName);
}

FVector AWeapon::GetAttackBoxHalfExtent() const
{
	return AttackBoxHalfExtent;
}

void AWeapon::DrawAttackBox(FColor Color/* = FColor::Red*/) const
{
#if ENABLE_DRAW_DEBUG
	FVector Pos = GetAttackBoxSocketPos();
	FVector Extent = AttackBoxHalfExtent * 2.0f * GetActorScale();
	FQuat Quat = GetActorRotation().Quaternion();
	DrawDebugBox(GetWorld(), Pos, Extent, Quat, Color, false, 5.0f);
#endif
}

float AWeapon::GetAttackDamage() const
{
	return DefaultDamage;
}

