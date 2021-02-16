// Fill out your copyright notice in the Description page of Project Settings.


#include "UiPlayerController.h"
#include "Blueprint/UserWidget.h"

void AUiPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UiWidgetInstance = CreateWidget<UUserWidget>(this, UiWidgetClass);
	return_if(UiWidgetInstance == nullptr);

	UiWidgetInstance->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UiWidgetInstance->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}