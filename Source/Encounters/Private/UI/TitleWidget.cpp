// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleWidget.h"
#include "Components/Button.h"
#include "EncGameInstance.h"

void UTitleWidget::NativeConstruct()
{
	Super::NativeConstruct();

	NewGameButton = Cast<UButton>(GetWidgetFromName(TEXT("btnNewGame")));
	ContinueButton = Cast<UButton>(GetWidgetFromName(TEXT("btnContinue")));
	ExitButton = Cast<UButton>(GetWidgetFromName(TEXT("btnExit")));

	return_if(NewGameButton == nullptr);
	return_if(ContinueButton == nullptr);
	return_if(ExitButton == nullptr);

	NewGameButton->OnClicked.AddDynamic(this, &UTitleWidget::OnNewGameButtonClicked);
	ContinueButton->OnClicked.AddDynamic(this, &UTitleWidget::OnContinueButtonClicked);
	ExitButton->OnClicked.AddDynamic(this, &UTitleWidget::OnExitButtonClicked);

	const FString& SlotName = UEncGameInstance::SaveGameSlotName;
	const int32& UserIndex = UEncGameInstance::SaveGameUserIndex;
	if (!UGameplayStatics::DoesSaveGameExist(SlotName, UserIndex))
	{
		ContinueButton->SetIsEnabled(false);
	}
}

void UTitleWidget::OnNewGameButtonClicked()
{
	GetGameInstance<UEncGameInstance>()->StartNewGame();
}

void UTitleWidget::OnContinueButtonClicked()
{
	GetGameInstance<UEncGameInstance>()->ContinueGame();
}

void UTitleWidget::OnExitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
