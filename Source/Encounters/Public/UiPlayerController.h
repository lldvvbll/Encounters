// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "GameFramework/PlayerController.h"
#include "UiPlayerController.generated.h"

class UUserWidget;

UCLASS()
class ENCOUNTERS_API AUiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadwrite, Category = UI, Meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> UiWidgetClass;

	UPROPERTY()
	UUserWidget* UiWidgetInstance;
};
