// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Weapon.h"
#include "Items/DataAssets/WeaponDataAsset.h"
#include "DrawDebugHelpers.h"

AWeapon::AWeapon()
{
	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISIONBOX"));

	RootComponent = SkMeshComp;
	CollisionBox->SetupAttachment(RootComponent);

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

void AWeapon::SetItemDataAsset(UItemDataAsset* DataAsset)
{
	Super::SetItemDataAsset(DataAsset);

	WeaponDataAsset = Cast<UWeaponDataAsset>(DataAsset);
}

const UWeaponDataAsset* AWeapon::GetWeaponDataAsset() const
{
	return WeaponDataAsset;
}

float AWeapon::GetAttackDamage() const
{
	return_if(WeaponDataAsset == nullptr, 0.0f);

	return WeaponDataAsset->Damage;
}

float AWeapon::GetAttackSpeed() const
{
	return_if(WeaponDataAsset == nullptr, 1.0f);

	return WeaponDataAsset->AttackSpeed;
}

FVector AWeapon::GetCollisionBoxPos() const
{
	return_if(CollisionBox == nullptr, FVector::ZeroVector);

	return CollisionBox->GetComponentLocation();
}

FCollisionShape AWeapon::GetCollisionBox() const
{
	return_if(CollisionBox == nullptr, FCollisionShape::MakeBox(FVector::ZeroVector));

	return CollisionBox->GetCollisionShape();
}

float AWeapon::GetUseStaminaOnAttack() const
{
	return_if(WeaponDataAsset == nullptr, -1.0f);

	return WeaponDataAsset->Stamina;
}

void AWeapon::DrawDebugCollisionBox(FColor Color/* = FColor::Red*/) const
{
#if ENABLE_DRAW_DEBUG
	if (CollisionBox != nullptr)
	{
		FVector Pos = GetCollisionBoxPos();
		FQuat Quat = GetActorRotation().Quaternion();
		DrawDebugBox(GetWorld(), Pos, CollisionBox->GetScaledBoxExtent(), Quat, Color, false, 5.0f);
	}
#endif
}
