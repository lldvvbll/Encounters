// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Shield.h"
#include "DrawDebugHelpers.h"

AShield::AShield()
{
    GaurdHalfAngle = 60.0f;
}

void AShield::PostInitializeComponents()
{
    Super::PostInitializeComponents();

    GaurdAngleCosine = FVector::ForwardVector.RotateAngleAxis(GaurdHalfAngle, FVector::UpVector) | FVector::ForwardVector;
}

float AShield::GetGaurdAngleCosine() const
{
    return GaurdAngleCosine;
}

void AShield::DrawGaurdAngle(FColor Color/* = FColor::Red*/) const
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
    for (float Angle = GaurdHalfAngle; Angle >= -GaurdHalfAngle; Angle -= 10.0f)
    {
        Positions.Emplace(CharPos + CharForward.RotateAngleAxis(Angle, FVector::UpVector));
    }
    Positions.Emplace(CharPos + CharForward.RotateAngleAxis(-GaurdHalfAngle, FVector::UpVector));
    Positions.Emplace(CharPos);

    for (int32 idx = 0; idx < Positions.Num() - 1; ++idx)
    {
        DrawDebugLine(GetWorld(), Positions[idx], Positions[idx + 1], Color, false, 5.0f);
    }
#endif
}
