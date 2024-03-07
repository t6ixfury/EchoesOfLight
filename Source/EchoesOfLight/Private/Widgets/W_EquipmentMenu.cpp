// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_EquipmentMenu.h"
#include "Widgets/W_StatBox.h"
#include "Widgets/W_EquipmentSlot.h"
#include "Widgets/W_InventoryPanel.h"
#include "Character/MainCharacter.h"
#include "Actors/Weapons/Base_Sword.h"
#include "ActorComponents/AC_DamageSystem.h"

//engine
#include "Components/ProgressBar.h"  
#include "Components/TextBlock.h"  
#include "Kismet/KismetMathLibrary.h"

void UW_EquipmentMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetMainCharacterReference();
	UpdateCharacterStats();
	UpdateStatProgressBars();

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
		AttackPower->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.AttackPower));
		AttackPower->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));

		//set magic power stat
		MagicPower->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.MagicPower));
		MagicPower->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
		
		//set Critical Hit rate stat
		CriticalHitRate->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.CriticalHitRate));
		CriticalHitRate->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));

		//Set AttackSpeed Stat
		AttackSpeed->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.AtttackSpeed));
		AttackSpeed->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
	}
}

void UW_EquipmentMenu::UpdateCharacterStats()
{
	if (MainCharacter)
	{
		//set health stat bar
		Health->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.Constitution));
		Health->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.MaxStatValue));

		//set defense stat bar
		Defense->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.DefensePower));
		Defense->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.MaxStatValue));

		//set stamina stat bar
		Stamina->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.Stamina));
		Stamina->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.MaxStatValue));

		// Set strength stat bar
		Strength->CurrentStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.Strength));
		Strength->MaximumStatValue->SetText(FText::AsNumber(MainCharacter->MainCharacterStats.MaxStatValue));
	}
}

void UW_EquipmentMenu::UpdateStatProgressBars()
{
	if (MainCharacter->LeftHandWeapon)
	{
		//Set equipment Stat progress bar.
		AttackPower->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.AttackPower) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
		MagicPower->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.MagicPower) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
		CriticalHitRate->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.CriticalHitRate) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
		AttackSpeed->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.AtttackSpeed) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->LeftHandWeapon->BaseAttackInfo.MaxStatValue));
	}
	if (MainCharacter)
	{
		//set Character Stat progress bar.
		Health->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.Constitution) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.MaxStatValue));
		Defense->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.DefensePower) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.MaxStatValue));
		Stamina->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.Stamina) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.MaxStatValue));
		Strength->StatProgressBar->SetPercent(UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.Strength) / UKismetMathLibrary::Conv_IntToFloat(MainCharacter->MainCharacterStats.MaxStatValue));
	}
}
