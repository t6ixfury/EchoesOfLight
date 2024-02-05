// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EquipmentMenu.generated.h"


class UTextBlock;
class UW_InventoryPanel;
class UW_EquipmentSlot;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_EquipmentMenu : public UUserWidget
{
	GENERATED_BODY()
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:

	// <Stat Values>

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackPower_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MagicPower_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CriticalHitRate_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* AttackSpeed_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Health_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* Stamina_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* StrengthPower_Value;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DefensePower_Value;


	// Widgets
	UPROPERTY(meta = (BindWidget))
		UW_InventoryPanel* InventoryWidget;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Amulet_Slot;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Weapon_Slot;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Netherband_Slot;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:

	void UpdateEquipmentStats();

	void UpdateCharacterStats();

	void UpdateSlots();
	
};
