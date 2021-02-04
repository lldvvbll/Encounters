// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Actors/Shield.h"
#include "Items/DataAssets/ShieldDataAsset.h"
#include "DrawDebugHelpers.h"

AShield::AShield()
{
    SkMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MESH"));

    GuardHalfAngle = 60.0f;
    GuardAngleCosine = FVector::ForwardVector.RotateAngleAxis(GuardHalfAngle, FVector::UpVector) | FVector::ForwardVector;
   
    RootComponent = SkMeshComp;
    SkMeshComp->SetCollisionProfileName(TEXT("NoCollision"));
}

float AShield::GetGuardAngleCosine() const
{
    return GuardAngleCosine;
}

float AShield::GetUseStaminaOnGuard() const
{
    TWeakObjectPtr<UShieldDataAsset> DataAsset = Cast<UShieldDataAsset>(ItemDataAsset);
    if (!DataAsset.IsValid())
        return -1.0;

    return DataAsset->Stamina;
}

void AShield::DrawGuardAngle(FColor Color/* = FColor::Red*/) const
{
#if ENABLE_DRAW_DEBUG
    AActor* Char = GetOwner();
    if (Char == nullptr)
        return;

    FVector CharPos = Char->GetActorLocation();
    FVector CharForward = Char->GetActorForwardVector() * 100.0f;

    static TArray<FVector> Positions;
    Positions.Reset();
    Positions.Emplace(CharPos);
    for (float Angle = GuardHalfAngle; Angle >= -GuardHalfAngle; Angle -= 10.0f)
    {
        Positions.Emplace(CharPos + CharForward.RotateAngleAxis(Angle, FVector::UpVector));
    }
    Positions.Emplace(CharPos + CharForward.RotateAngleAxis(-GuardHalfAngle, FVector::UpVector));
    Positions.Emplace(CharPos);

    for (int32 idx = 0; idx < Positions.Num() - 1; ++idx)
    {
        DrawDebugLine(GetWorld(), Positions[idx], Positions[idx + 1], Color, false, 5.0f);
    }
#endif
}
