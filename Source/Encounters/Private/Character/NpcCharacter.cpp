// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/NpcCharacter.h"
#include "Character/PlayerCharacter.h"
#include "Character/EncCharacterStateComponent.h"
#include "Character/InventoryComponent.h"
#include "Character/DataAssets/NpcDataAsset.h"
#include "Components/WidgetComponent.h"
#include "UI/CharacterWidget.h"
#include "Items/DataAssets/WeaponDataAsset.h"
#include "Items/DataAssets/ShieldDataAsset.h"
#include "EncAIController.h"
#include "EncGameInstance.h"
#include "EncAssetManager.h"
#include "EncPlayerState.h"

ANpcCharacter::ANpcCharacter()
{
	AIControllerClass = AEncAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	HpBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));

	HpBarWidget->SetupAttachment(GetCapsuleComponent());

	static ConstructorHelpers::FClassFinder<UCharacterWidget> UI_CHAR(
		TEXT("/Game/Encounters/UI/UI_HpBar.UI_HpBar_C"));
	if (UI_CHAR.Succeeded())
	{
		HpBarWidget->SetWidgetClass(UI_CHAR.Class);
		HpBarWidget->SetDrawSize(FVector2D(150.0f, 50.0f));
		HpBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
		HpBarWidget->SetWidgetSpace(EWidgetSpace::Screen);
		HpBarWidget->SetVisibility(false);
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BB_Data(
		TEXT("/Game/Encounters/AI/BB_Knight.BB_Knight"));
	if (BB_Data.Succeeded())
	{
		BlackboardData = BB_Data.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BT_OBJECT(
		TEXT("/Game/Encounters/AI/BT_Knight.BT_Knight"));
	if (BT_OBJECT.Succeeded())
	{
		BehaviorTree = BT_OBJECT.Object;
	}
}

void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (auto CharWidget = Cast<UCharacterWidget>(HpBarWidget->GetUserWidgetObject()))
	{
		CharWidget->BindCharacterState(CharacterState);
	}
}

float ANpcCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (bDead)
	{
		if (auto PlayerChar = Cast<APlayerCharacter>(DamageCauser))
		{
			PlayerChar->GivePoint(NpcDataAsset->DropPoint);
		}
	}
	else if (FinalDamage > 0.0f)
	{
		HpBarWidget->SetVisibility(true);
	}

	return FinalDamage;
}

void ANpcCharacter::RotateBySavedInput()
{
	if (SavedInput.IsNearlyZero())
		return;

	SetActorRotation(SavedInput.Rotation(), ETeleportType::TeleportPhysics);
	SavedInput = FVector::ZeroVector;
}

void ANpcCharacter::Dead()
{
	Super::Dead();

	HpBarWidget->SetVisibility(false);
	GetController<AEncAIController>()->StopAI();

	OnNpcDead.Broadcast(this);
}

UBehaviorTree* ANpcCharacter::GetBehaviorTree() const
{
	return BehaviorTree;
}

UBlackboardData* ANpcCharacter::GetBlackboardData() const
{
	return BlackboardData;
}

void ANpcCharacter::SetNpcDataAsset(UNpcDataAsset* DataAsset)
{
	return_if(DataAsset == nullptr);

	NpcDataAsset = DataAsset;

	CharacterState->SetAttackPower(DataAsset->AttackPower);
	CharacterState->SetMaxHP(DataAsset->HP);
	CharacterState->SetHP(DataAsset->HP);
	CharacterState->SetMaxStamina(DataAsset->Stamina);
	CharacterState->SetStamina(DataAsset->Stamina);
	CharacterState->SetRollingSpeed(DataAsset->RollingSpeed);
	CharacterState->SetRollingVelocityRate(DataAsset->RollingVelocityRate);

	Inventory->AddItemFromSaveItemDatas(DataAsset->Items);
}

float ANpcCharacter::GetDetectionRange() const
{
	return_if(NpcDataAsset == nullptr, 0.0f);

	return NpcDataAsset->DetectionRange;
}

float ANpcCharacter::GetAttackRange() const
{
	return_if(NpcDataAsset == nullptr, 0.0f);

	return NpcDataAsset->AttackRange;
}
