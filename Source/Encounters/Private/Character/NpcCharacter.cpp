// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NpcCharacter.h"
#include "EncAIController.h"
#include "Components/WidgetComponent.h"

ANpcCharacter::ANpcCharacter()
{
	AIControllerClass = AEncAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HPBAR(TEXT("/Game/Encounters/UI/UI_HpBar.UI_HpBar_C"));
	if (UI_HPBAR.Succeeded())
	{
		HpBarWidget->SetWidgetClass(UI_HPBAR.Class);
		HpBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
	}
	HpBarWidget->SetupAttachment(GetCapsuleComponent());
	HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
}