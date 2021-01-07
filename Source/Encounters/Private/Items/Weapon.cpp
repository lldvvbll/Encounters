// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	RootComponent = SkMeshComp;

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	AttachRotator = FRotator::ZeroRotator;
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

