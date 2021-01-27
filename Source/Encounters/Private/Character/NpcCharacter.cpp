// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NpcCharacter.h"
#include "EncAIController.h"
#include "Components/WidgetComponent.h"
#include "UI/CharacterWidget.h"
#include "Character/EncCharacterStateComponent.h"

ANpcCharacter::ANpcCharacter()
{
	AIControllerClass = AEncAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	static ConstructorHelpers::FClassFinder<UCharacterWidget> UI_CHAR(
		TEXT("/Game/Encounters/UI/UI_HpBar.UI_HpBar_C"));
	if (UI_CHAR.Succeeded())
	{
		HpBarWidget->SetWidgetClass(UI_CHAR.Class);
		HpBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	HpBarWidget->SetupAttachment(GetCapsuleComponent());
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HpBarWidget->SetVisibility(false);
}

void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto CharWidget = Cast<UCharacterWidget>(HpBarWidget->GetUserWidgetObject()))
	{
		CharWidget->BindCharacterState(CharacterState);
	}
}

float ANpcCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (FinalDamage > 0.0f && !bDead)
	{
		HpBarWidget->SetVisibility(true);
	}

	return FinalDamage;
}

void ANpcCharacter::Dead()
{
	Super::Dead();

	HpBarWidget->SetVisibility(false);
}
