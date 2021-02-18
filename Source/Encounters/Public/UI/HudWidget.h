// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Blueprint/UserWidget.h"
#include "HudWidget.generated.h"

class UEncCharacterStateComponent;
class UProgressBar;
class UTextBlock;

UCLASS()
class ENCOUNTERS_API UHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterState(UEncCharacterStateComponent* CharacterState);

protected:
	virtual void NativeConstruct() override;
	void UpdateCharacterState();

private:
	TWeakObjectPtr<UEncCharacterStateComponent> CharacterState;

	UPROPERTY()
	UProgressBar* HpBar;

	UPROPERTY()
	UProgressBar* StaminaBar;

	UPROPERTY()
	UTextBlock* MaxHpText;

	UPROPERTY()
	UTextBlock* MaxStaminaText;

	UPROPERTY()
	UTextBlock* CurrentHpText;

	UPROPERTY()
	UTextBlock* CurrentStaminaText;
};
