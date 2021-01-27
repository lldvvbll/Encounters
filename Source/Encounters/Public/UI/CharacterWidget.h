// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Encounters.h"
#include "Blueprint/UserWidget.h"
#include "CharacterWidget.generated.h"

class UEncCharacterStateComponent;
class UProgressBar;

UCLASS()
class ENCOUNTERS_API UCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void BindCharacterState(UEncCharacterStateComponent* NewCharacterState);

protected:
	virtual void NativeConstruct() override;

	void UpdateHpWidget();

private:
	UPROPERTY(VisibleAnywhere, Category = StateComponent, Meta = (AllowPrivateAccess = true))
	UEncCharacterStateComponent* CharacterState;

	UPROPERTY()
	UProgressBar* HpProgressBar;
};
