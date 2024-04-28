// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryToolTip.generated.h"


class UW_InventorySlot;
class UTextBlock;


/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UInventoryToolTip : public UUserWidget
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
public:
	//values come from ItemData

	UPROPERTY(VisibleAnywhere)
	UW_InventorySlot* InventorySlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* StaminaRestorationAmountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* StaminaRestorationAmountValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* HealthRestorationAmountText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* HealthRestorationAmountValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackPowerValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackPower;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MagicPowerValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MagicPower;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CriticalHitValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CriticalHit;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackSpeedValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackSpeed;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* HealthValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* StaminaValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Stamina;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* StrengthValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Strength;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DefenseValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Defense;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* WeaponStatText;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CharacterStatText;

protected:


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:

	virtual void NativeConstruct() override;

};
