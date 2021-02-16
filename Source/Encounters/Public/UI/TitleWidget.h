// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Blueprint/UserWidget.h"
#include "TitleWidget.generated.h"

class UButton;

UCLASS()
class ENCOUNTERS_API UTitleWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnNewGameButtonClicked();

	UFUNCTION()
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

private:
	UPROPERTY()
	UButton* NewGameButton;

	UPROPERTY()
	UButton* ContinueButton;

	UPROPERTY()
	UButton* ExitButton;
};
