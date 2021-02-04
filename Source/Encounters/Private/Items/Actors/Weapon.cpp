// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Weapon.h"
#include "Items/DataAssets/WeaponDataAsset.h"
#include "DrawDebugHelpers.h"

AWeapon::AWeapon()
{
	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));

	DefaultDamage = 10.0f;

	RootComponent = SkMeshComp;
	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

float AWeapon::GetAttackDamage() const
{
	return DefaultDamage;
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

float AWeapon::GetUseStaminaOnAttack() const
{
	TWeakObjectPtr<UWeaponDataAsset> DataAsset = Cast<UWeaponDataAsset>(ItemDataAsset);
	if (!DataAsset.IsValid())
		return -1.0;

	return DataAsset->Stamina;
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
