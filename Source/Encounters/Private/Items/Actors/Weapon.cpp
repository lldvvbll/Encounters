// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Weapon.h"
#include "Items/DataAssets/WeaponDataAsset.h"
#include "DrawDebugHelpers.h"

AWeapon::AWeapon()
{
	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("COLLISIONBOX"));

	DefaultDamage = 10.0f;

	RootComponent = SkMeshComp;
	CollisionBox->SetupAttachment(RootComponent);

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	CollisionBox->SetCollisionProfileName(TEXT("NoCollision"));
}

float AWeapon::GetAttackDamage() const
{
	return DefaultDamage;
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
	TWeakObjectPtr<UWeaponDataAsset> DataAsset = Cast<UWeaponDataAsset>(ItemDataAsset);
	if (!DataAsset.IsValid())
		return -1.0;

	return DataAsset->Stamina;
}

void AWeapon::DrawAttackBox(FColor Color/* = FColor::Red*/) const
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
