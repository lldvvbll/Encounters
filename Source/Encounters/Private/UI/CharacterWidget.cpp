// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CharacterWidget.h"
#include "Character/EncCharacterStateComponent.h"
#include "Components/ProgressBar.h"

void UCharacterWidget::BindCharacterState(UEncCharacterStateComponent* NewCharacterState)
{
	return_if(NewCharacterState == nullptr);

	CharacterState = NewCharacterState;
	CharacterState->OnHpChanged.AddUObject(this, &UCharacterWidget::UpdateHpWidget);
}

void UCharacterWidget::NativeConstruct()
{
	Super::NativeConstruct();

	HpProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HpBar")));
	return_if(HpProgressBar == nullptr);

	UpdateHpWidget();
}

void UCharacterWidget::UpdateHpWidget()
{
	if (HpProgressBar != nullptr && CharacterState != nullptr)
	{
		HpProgressBar->SetPercent(CharacterState->GetHpRatio());
	}
}
