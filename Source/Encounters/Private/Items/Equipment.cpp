// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Equipment.h"

// Sets default values
AEquipment::AEquipment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));
	RootComponent = SkMeshComp;

	SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FRotator AEquipment::GetAttachRotator() const
{
	return AttachRotator;
}
