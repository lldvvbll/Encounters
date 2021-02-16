// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/TitleWidget.h"
#include "Components/Button.h"
#include "EncAssetManager.h"
#include "EncGameInstance.h"
#include "Stage/DataAssets/StageDataAsset.h"

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
}

void UTitleWidget::OnNewGameButtonClicked()
{
	UStageDataAsset* StageDataAsset = GetGameInstance<UEncGameInstance>()->GetStageDataAssetByIndex(0);
	return_if(StageDataAsset == nullptr);

	UGameplayStatics::DeleteGameInSlot(UEncGameInstance::SaveGameSlotName, UEncGameInstance::SaveGameUserIndex);
	UGameplayStatics::OpenLevel(GetWorld(), StageDataAsset->LevelAssetId.PrimaryAssetName);
}

void UTitleWidget::OnContinueButtonClicked()
{
	UStageDataAsset* StageDataAsset = GetGameInstance<UEncGameInstance>()->GetStageDataAssetByIndex(0);
	return_if(StageDataAsset == nullptr);

	UGameplayStatics::OpenLevel(GetWorld(), StageDataAsset->LevelAssetId.PrimaryAssetName);
}

void UTitleWidget::OnExitButtonClicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
