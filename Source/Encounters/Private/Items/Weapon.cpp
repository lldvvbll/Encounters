// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	RootComponent = SkMeshComp;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_WEAPON(TEXT("/Game/Weapon_Pack/Skeletal_Mesh/SK_Sword.SK_Sword"));
	if (SK_WEAPON.Succeeded())
	{
		SkMeshComp->SetSkeletalMesh(SK_WEAPON.Object);
	}

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	SetActorRelativeScale3D(FVector(0.75f, 0.75f, 0.75f));
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

