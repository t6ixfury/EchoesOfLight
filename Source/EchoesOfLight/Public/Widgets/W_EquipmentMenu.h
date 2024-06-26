// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EquipmentMenu.generated.h"


class UTextBlock;
class UW_InventoryPanel;
class UW_EquipmentSlot;
class UW_StatBox;
class AMainCharacter;
class UItemBase;
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

	// <Weapon Stat Values>

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* AttackPower;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* MagicPower;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* CriticalHitRate;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* AttackSpeed;

	// <Character Stat Values>

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* Health;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* Stamina;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* Strength;

	UPROPERTY(meta = (BindWidget))
		UW_StatBox* Defense;



	// Widgets
	UPROPERTY(meta = (BindWidget))
		UW_InventoryPanel* InventoryWidget;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Amulet_Slot;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Weapon_Slot;

	UPROPERTY(meta = (BindWidget))
		UW_EquipmentSlot* Netherband_Slot;

	UPROPERTY()
		AMainCharacter* MainCharacter;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:

	virtual void NativeOnInitialized() override;

	void SetMainCharacterReference();

	//Updates the Text for the Equipment stats on the stat bar
	void UpdateEquipmentStats();

	//Updates the Text for the Character Stats on the stat bar
	void UpdateCharacterStats();

	//Updates widget UI
	void UpdateEquipmentWidget();

	//Updates the stat progress bar for the equipment stats and the character stats
	void UpdateStatProgressBars();

	void SaveEquipment();

	void LoadEquipmentSlots();
	
	void RemoveAmulet();

	void RemoveNetherBand();

	void RemoveWeapon();

	void AddAmulet(UItemBase* item);

	void AddNetherBand(UItemBase* item);

	void AddWeapon(UItemBase* item);
	
	
	
};
