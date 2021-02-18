// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PlayerStateWidget.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "EncPlayerController.h"
#include "EncPlayerState.h"
#include "EncGameInstance.h"
#include "Character/PlayerCharacter.h"
#include "DataStructures.h"
#include "EncSaveGame.h"

void UPlayerStateWidget::Bind(bool bGamePause)
{
	bOnGamePause = bGamePause;

	if (bOnGamePause)
	{
		auto PlayerController = Cast<AEncPlayerController>(GetOwningPlayer());
		return_if(PlayerController == nullptr);

		APlayerCharacter* PlayerCharacter = PlayerController->GetPlayerCharacter();
		return_if(PlayerCharacter == nullptr);

		PlayerState = PlayerController->GetPlayerState<AEncPlayerState>();
		PlayerChar = PlayerCharacter;
	}
}

void UPlayerStateWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TitleText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtTitle")));
	LevelText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevel")));
	PointText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtPoint")));
	StrengthText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtStrength")));
	StrengthUpButton = Cast<UButton>(GetWidgetFromName(TEXT("btnStrength")));
	AgilityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtAgility")));
	AgilityUpButton = Cast<UButton>(GetWidgetFromName(TEXT("btnAgility")));
	VitalityText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtVitality")));
	VitalityUpButton = Cast<UButton>(GetWidgetFromName(TEXT("btnVitality")));
	EnduranceText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtEndurance")));
	EnduranceUpButton = Cast<UButton>(GetWidgetFromName(TEXT("btnEndurance")));
	LevelUpPointText = Cast<UTextBlock>(GetWidgetFromName(TEXT("txtLevelUpPoint")));
	GoToTitleButton = Cast<UButton>(GetWidgetFromName(TEXT("btnGoToTitle")));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("btnContinue")));

	return_if(TitleText == nullptr);
	return_if(LevelText == nullptr);
	return_if(PointText == nullptr);
	return_if(StrengthText == nullptr);
	return_if(StrengthUpButton == nullptr);
	return_if(AgilityText == nullptr);
	return_if(AgilityUpButton == nullptr);
	return_if(VitalityText == nullptr);
	return_if(VitalityUpButton == nullptr);
	return_if(EnduranceText == nullptr);
	return_if(EnduranceUpButton == nullptr);
	return_if(LevelUpPointText == nullptr);
	return_if(GoToTitleButton == nullptr);
	return_if(ContinueButton == nullptr);

	StrengthUpButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnStrenthUpButtonClicked);
	AgilityUpButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnAgilityUpButtonClicked);
	VitalityUpButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnVitalityUpButtonClicked);
	EnduranceUpButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnEnduranceUpButtonClicked);
	GoToTitleButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnGoToTitleButtonClicked);
	ContinueButton->OnClicked.AddDynamic(this, &UPlayerStateWidget::OnContinueButtonClicked);

	if (bOnGamePause)
	{
		StrengthUpButton->SetVisibility(ESlateVisibility::Hidden);
		AgilityUpButton->SetVisibility(ESlateVisibility::Hidden);
		VitalityUpButton->SetVisibility(ESlateVisibility::Hidden);
		EnduranceUpButton->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		TitleText->SetText(FText::FromString(TEXT("YOU DIED")));

		const FString& SlotName = UEncGameInstance::SaveGameSlotName;
		const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;
		if (UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
		{
			SavedGame = Cast<UEncSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName, UserIndex));
		}

		CheckPlayerAttributeUpButtonsVisibility();
	}

	SetPlayerAttributeText();
}

void UPlayerStateWidget::OnStrenthUpButtonClicked()
{
	return_if(SavedGame == nullptr);

	SavedGame->PlayerState.Strength++;
	OnPlayerAttributeUp();
}

void UPlayerStateWidget::OnAgilityUpButtonClicked()
{
	return_if(SavedGame == nullptr);

	SavedGame->PlayerState.Agility++;
	OnPlayerAttributeUp();
}

void UPlayerStateWidget::OnVitalityUpButtonClicked()
{
	return_if(SavedGame == nullptr);

	SavedGame->PlayerState.Vitality++;
	OnPlayerAttributeUp();
}

void UPlayerStateWidget::OnEnduranceUpButtonClicked()
{
	return_if(SavedGame == nullptr);

	SavedGame->PlayerState.Endurance++;
	OnPlayerAttributeUp();
}

void UPlayerStateWidget::OnGoToTitleButtonClicked()
{
	if (bOnGamePause)
	{
		auto PlayerController = Cast<AEncPlayerController>(GetOwningPlayer());
		return_if(PlayerController == nullptr);

		PlayerController->SaveGame();
	}

	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Title"));
}

void UPlayerStateWidget::OnContinueButtonClicked()
{
	if (bOnGamePause)
	{
		auto PlayerController = Cast<AEncPlayerController>(GetOwningPlayer());
		return_if(PlayerController == nullptr);

		RemoveFromParent();
		PlayerController->ChangeInputMode(true);
		PlayerController->SetPause(false);
	}
	else
	{
		GetGameInstance<UEncGameInstance>()->ContinueGame();
	}
}

void UPlayerStateWidget::SetPlayerAttributeText()
{
	if (bOnGamePause)
	{
		return_if(!PlayerState.IsValid());
		return_if(!PlayerChar.IsValid());

		LevelText->SetText(FText::FromString(FString::FromInt(PlayerState->GetLevel())));
		PointText->SetText(FText::FromString(FString::FromInt(PlayerState->GetPoint())));
		StrengthText->SetText(FText::FromString(FString::FromInt(PlayerState->GetStrength())));
		AgilityText->SetText(FText::FromString(FString::FromInt(PlayerState->GetAgility())));
		VitalityText->SetText(FText::FromString(FString::FromInt(PlayerState->GetVitality())));
		EnduranceText->SetText(FText::FromString(FString::FromInt(PlayerState->GetEndurance())));

		auto GameInstance = GetGameInstance<UEncGameInstance>();
		return_if(GameInstance == nullptr);

		int32 LvUpPoint = GameInstance->GetLevelUpPoint(PlayerState->GetLevel());
		LevelUpPointText->SetText(FText::FromString(FString::FromInt(LvUpPoint)));
	}
	else
	{
		return_if(SavedGame == nullptr);

		LevelText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Level)));
		PointText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Point)));
		StrengthText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Strength)));
		AgilityText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Agility)));
		VitalityText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Vitality)));
		EnduranceText->SetText(FText::FromString(FString::FromInt(SavedGame->PlayerState.Endurance)));
	}
}

void UPlayerStateWidget::CheckPlayerAttributeUpButtonsVisibility()
{
	auto GameInstance = GetGameInstance<UEncGameInstance>();
	return_if(GameInstance == nullptr);
	return_if(SavedGame == nullptr);

	int32 LvUpPoint = GameInstance->GetLevelUpPoint(SavedGame->PlayerState.Level);
	return_if(LvUpPoint < 0);

	ESlateVisibility VisibilityByPoint = 
		(SavedGame->PlayerState.Point >= LvUpPoint) ? ESlateVisibility::Visible : ESlateVisibility::Hidden;

	StrengthUpButton->SetVisibility((SavedGame->PlayerState.Strength >= 10) ? ESlateVisibility::Hidden : VisibilityByPoint);
	AgilityUpButton->SetVisibility((SavedGame->PlayerState.Agility >= 10) ? ESlateVisibility::Hidden : VisibilityByPoint);
	VitalityUpButton->SetVisibility((SavedGame->PlayerState.Vitality >= 10) ? ESlateVisibility::Hidden : VisibilityByPoint);
	EnduranceUpButton->SetVisibility((SavedGame->PlayerState.Endurance >= 10) ? ESlateVisibility::Hidden : VisibilityByPoint);

	LevelUpPointText->SetText(FText::FromString(FString::FromInt(LvUpPoint)));
}

void UPlayerStateWidget::OnPlayerAttributeUp()
{
	return_if(SavedGame == nullptr);

	auto GameInstance = GetGameInstance<UEncGameInstance>();
	return_if(GameInstance == nullptr);

	int32 LvUpPoint = GameInstance->GetLevelUpPoint(SavedGame->PlayerState.Level);
	SavedGame->PlayerState.Point = FMath::Max(0, SavedGame->PlayerState.Point - LvUpPoint);
	SavedGame->PlayerState.Level++;

	const FString& SlotName = UEncGameInstance::SaveGameSlotName;
	const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;

	UEncSaveGame* NewSaveGame = NewObject<UEncSaveGame>();
	return_if(NewSaveGame == nullptr);

	NewSaveGame->Copy(SavedGame);
	SavedGame = NewSaveGame;

	if (!UGameplayStatics::SaveGameToSlot(NewSaveGame, SlotName, UserIndex))
	{
		LOG(Error, TEXT("SaveGame Error"));
	}

	CheckPlayerAttributeUpButtonsVisibility();
	SetPlayerAttributeText();
}
