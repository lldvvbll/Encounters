// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStateWidget.generated.h"

class UTextBlock;
class UButton;
class AEncPlayerState;
class APlayerCharacter;
class UEncSaveGame;

UCLASS()
class ENCOUNTERS_API UPlayerStateWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Bind(bool bGamePause);

protected:
	virtual void NativeConstruct() override;

private:
	UFUNCTION()
	void OnStrenthUpButtonClicked();

	UFUNCTION()
	void OnAgilityUpButtonClicked();

	UFUNCTION()
	void OnVitalityUpButtonClicked();

	UFUNCTION()
	void OnEnduranceUpButtonClicked();

	UFUNCTION()
	void OnGoToTitleButtonClicked();

	UFUNCTION()
	void OnContinueButtonClicked();

	void SetPlayerAttributeText();
	void CheckPlayerAttributeUpButtonsVisibility();
	void OnPlayerAttributeUp();

private:
	TWeakObjectPtr<AEncPlayerState> PlayerState;
	TWeakObjectPtr<APlayerCharacter> PlayerChar;
	UEncSaveGame* SavedGame;

	UPROPERTY(Transient)
	bool bOnGamePause;

	UPROPERTY()
	UTextBlock* TitleText;

	UPROPERTY()
	UTextBlock* LevelText;

	UPROPERTY()
	UTextBlock* PointText;

	UPROPERTY()
	UTextBlock* StrengthText;

	UPROPERTY()
	UButton* StrengthUpButton;

	UPROPERTY()
	UTextBlock* AgilityText;

	UPROPERTY()
	UButton* AgilityUpButton;

	UPROPERTY()
	UTextBlock* VitalityText;

	UPROPERTY()
	UButton* VitalityUpButton;

	UPROPERTY()
	UTextBlock* EnduranceText;

	UPROPERTY()
	UButton* EnduranceUpButton;

	UPROPERTY()
	UTextBlock* LevelUpPointText;

	UPROPERTY()
	UButton* GoToTitleButton;

	UPROPERTY()
	UButton* ContinueButton;
};
