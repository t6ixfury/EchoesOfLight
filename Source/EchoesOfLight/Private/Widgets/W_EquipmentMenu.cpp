// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_EquipmentMenu.h"
#include "Widgets/W_StatBox.h"
#include "Widgets/W_EquipmentSlot.h"
#include "Widgets/W_InventoryPanel.h"
#include "Character/MainCharacter.h"
#include "Actors/Weapons/Base_Sword.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Save/EchoesGameInstance.h"
#include "Save/Save_Equipment.h"


//engine
#include "Components/ProgressBar.h"  
#include "Components/TextBlock.h"  
#include "Kismet/GameplayStatics.h"


void UW_EquipmentMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetMainCharacterReference();
	UpdateCharacterStats();
	UpdateStatProgressBars();

	Weapon_Slot->EquipmentType = EItemType::Weapon;
	Amulet_Slot->EquipmentType = EItemType::Amulet;
	Netherband_Slot->EquipmentType = EItemType::Netherband;

}

void UW_EquipmentMenu::SetMainCharacterReference()
{
	APlayerController* characterController = GetOwningPlayer();

	if (characterController)
	{
		AMainCharacter* characterRef = Cast<AMainCharacter>(characterController->GetPawn());
		if (characterRef)
		{
			MainCharacter = characterRef;
		}
	}
}

void UW_EquipmentMenu::UpdateEquipmentStats()
{
	if (MainCharacter->LeftHandWeapon)
	{
		// Set the Attack power stat to be properly represented int the widget.
		AttackPower->SetStatValues(MainCharacter->LeftHandWeapon->BaseAttackInfo.AttackPower, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);

		//set magic power stat
		MagicPower->SetStatValues(MainCharacter->LeftHandWeapon->BaseAttackInfo.MagicPower, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);

		//set Critical Hit rate stat
		CriticalHitRate->SetStatValues(MainCharacter->LeftHandWeapon->BaseAttackInfo.CriticalHitRate, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);

		//Set AttackSpeed Stat
		AttackSpeed->SetStatValues(MainCharacter->LeftHandWeapon->BaseAttackInfo.AtttackSpeed, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);
		UE_LOG(LogTemp, Warning, TEXT("Equipment stats not Lefthand null"));
	}
	else
	{
		// Set the Attack power stat to be properly represented int the widget.
		AttackPower->SetStatValues(1, 99);

		//set magic power stat
		MagicPower->SetStatValues(1, 99);

		//set Critical Hit rate stat
		CriticalHitRate->SetStatValues(1, 99);

		//Set AttackSpeed Stat
		AttackSpeed->SetStatValues(1, 99);
		UE_LOG(LogTemp, Warning, TEXT("Equipment stats Lefthand null"));
	}
}

void UW_EquipmentMenu::UpdateCharacterStats()
{
	if (MainCharacter)
	{
		//set health stat bar
		Health->SetStatValues(MainCharacter->MainCharacterStats.Constitution, MainCharacter->MainCharacterStats.MaxStatValue);

		//set defense stat bar
		Defense->SetStatValues(MainCharacter->MainCharacterStats.DefensePower, MainCharacter->MainCharacterStats.MaxStatValue);

		//set stamina stat bar
		Stamina->SetStatValues(MainCharacter->MainCharacterStats.Stamina, MainCharacter->MainCharacterStats.MaxStatValue);

		// Set strength stat bar
		Strength->SetStatValues(MainCharacter->MainCharacterStats.Strength, MainCharacter->MainCharacterStats.MaxStatValue);
	}
}

void UW_EquipmentMenu::UpdateEquipmentWidget()
{
	UpdateCharacterStats();
	UpdateStatProgressBars();
	UpdateEquipmentStats();
}

void UW_EquipmentMenu::UpdateStatProgressBars()
{
	if (MainCharacter->LeftHandWeapon)
	{
		//Set equipment Stat progress bar.
		AttackPower->SetProgressBarPercentage(MainCharacter->LeftHandWeapon->BaseAttackInfo.AttackPower, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);
		MagicPower->SetProgressBarPercentage(MainCharacter->LeftHandWeapon->BaseAttackInfo.MagicPower, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);
		CriticalHitRate->SetProgressBarPercentage(MainCharacter->LeftHandWeapon->BaseAttackInfo.CriticalHitRate, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);
		AttackSpeed->SetProgressBarPercentage(MainCharacter->LeftHandWeapon->BaseAttackInfo.AtttackSpeed, MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue);
	}
	else
	{
		AttackPower->SetProgressBarPercentage(1, 99);
		MagicPower->SetProgressBarPercentage(1, 99);
		CriticalHitRate->SetProgressBarPercentage(1, 99);
		AttackSpeed->SetProgressBarPercentage(1, 99);

	}
	if (MainCharacter)
	{
		//set Character Stat progress bar.
		Health->SetProgressBarPercentage(MainCharacter->MainCharacterStats.Constitution, MainCharacter->MainCharacterStats.MaxStatValue);
		Defense->SetProgressBarPercentage(MainCharacter->MainCharacterStats.DefensePower, MainCharacter->MainCharacterStats.MaxStatValue);
		Stamina->SetProgressBarPercentage(MainCharacter->MainCharacterStats.Stamina, MainCharacter->MainCharacterStats.MaxStatValue);
		Strength->SetProgressBarPercentage(MainCharacter->MainCharacterStats.Strength, MainCharacter->MainCharacterStats.MaxStatValue);
	}
}

void UW_EquipmentMenu::SaveEquipment()
{
	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (USave_Equipment* save = NewObject<USave_Equipment>(this, USave_Equipment::StaticClass()))
		{
			if (!Amulet_Slot->SlotItemId.IsNone())
			{
				save->sAmuletID = Amulet_Slot->SlotItemId;
			}
			if (!Weapon_Slot->SlotItemId.IsNone())
			{
				save->sWeaponID = Weapon_Slot->SlotItemId;
			}
			if (!Netherband_Slot->SlotItemId.IsNone())
			{
				save->sWeaponID = Netherband_Slot->SlotItemId;
			}

			UGameplayStatics::SaveGameToSlot(save, GameInstance->EquipmentDataSlot, 0);
		}

	}
}

void UW_EquipmentMenu::LoadEquipmentSlots()
{
	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		if (UGameplayStatics::DoesSaveGameExist(GameInstance->EquipmentDataSlot, 0))
		{
			if (USave_Equipment* LoadData = Cast<USave_Equipment>(UGameplayStatics::LoadGameFromSlot(GameInstance->EquipmentDataSlot, 0)))
			{
				if (IsValid(Amulet_Slot) && !LoadData->sAmuletID.IsNone() && IsValid(Amulet_Slot->AmuletDataTable))
				{
					Amulet_Slot->SlotItemId = LoadData->sAmuletID;
					Amulet_Slot->CreateItem(Amulet_Slot->AmuletDataTable, Amulet_Slot->SlotItemId);
					Amulet_Slot->SetIconImage();
				}
				if (IsValid(Weapon_Slot) && !LoadData->sWeaponID.IsNone() && IsValid(Weapon_Slot->WeaponDataTable))
				{
					Weapon_Slot->SlotItemId = LoadData->sWeaponID;
					Weapon_Slot->CreateItem(Weapon_Slot->WeaponDataTable, Weapon_Slot->SlotItemId);
					Weapon_Slot->SetIconImage();
				}
				if (IsValid(Netherband_Slot) && !LoadData->sNetherbandID.IsNone() && IsValid(Netherband_Slot->NetherBandDataTable))
				{
					Netherband_Slot->SlotItemId = LoadData->sNetherbandID;
					Netherband_Slot->CreateItem(Netherband_Slot->NetherBandDataTable, Netherband_Slot->SlotItemId);
					Netherband_Slot->SetIconImage();
				}
			}
		}
	}
}

