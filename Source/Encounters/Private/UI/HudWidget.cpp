// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HudWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Character/EncCharacterStateComponent.h"

void UHudWidget::BindCharacterState(UEncCharacterStateComponent* NewCharacterState)
{
	return_if(NewCharacterState == nullptr);

	CharacterState = NewCharacterState;
	CharacterState->OnHpChanged.AddUObject(this, &UHudWidget::UpdateCharacterState);
	CharacterState->OnStaminaChanged.AddUObject(this, &UHudWidget::UpdateCharacterState);
	CharacterState->OnMaxStaminaChanged.AddUObject(this, &UHudWidget::UpdateCharacterState);
	CharacterState->OnMaxHpChanged.AddUObject(this, &UHudWidget::UpdateCharacterState);
}

void UHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbHP")));
	StaminaBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("pbStamina")));
	MaxHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMaxHP")));
	MaxStaminaText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtMaxStamina")));
	CurrentHpText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurHP")));
	CurrentStaminaText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtCurStamina")));

	return_if(HpBar == nullptr);
	return_if(StaminaBar == nullptr);
	return_if(MaxHpText == nullptr);
	return_if(MaxStaminaText == nullptr);
	return_if(CurrentHpText == nullptr);
	return_if(CurrentStaminaText == nullptr);
}

void UHudWidget::UpdateCharacterState()
{
	if (CharacterState == nullptr)
		return;

	HpBar->SetPercent(CharacterState->GetHpRatio());
	StaminaBar->SetPercent(CharacterState->GetStaminaRatio());
	CurrentHpText->SetText(FText::FromString(FString::FromInt(CharacterState->GetHP())));
	CurrentStaminaText->SetText(FText::FromString(FString::FromInt(CharacterState->GetStamina())));
	MaxHpText->SetText(FText::FromString(FString::FromInt(CharacterState->GetMaxHP())));
	MaxStaminaText->SetText(FText::FromString(FString::FromInt(CharacterState->GetMaxStamina())));
}
