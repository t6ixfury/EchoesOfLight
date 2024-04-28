// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/InventoryToolTip.h"
#include "Widgets/W_InventorySlot.h"
#include "Widgets/W_InventoryPanel.h"
#include "Actors/Items/ItemBase.h"

//engine
#include "Components/TextBlock.h"

void UInventoryToolTip::NativeConstruct()
{
	Super::NativeConstruct();

	if (InventorySlotBeingHovered)
	{
		if (const UItemBase* ItemBeingHovered = InventorySlotBeingHovered->GetItemReference())
		{
			//switch sets the setting for which fields should be visible in the tool tip
			switch (ItemBeingHovered->ItemType)
			{
			case EItemType::Amulet:
				ItemType->SetText(FText::FromString("Amulet"));
				CharacterStatText->SetVisibility(ESlateVisibility::Collapsed);


				AttackPower->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.AttackPower));
				CriticalHit->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.CriticalHitRate));
				MagicPower->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.MagicPower));
				AttackSpeed->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.AtttackSpeed));


				//Remove Character stats visibility
				HealthValue->SetVisibility(ESlateVisibility::Collapsed);
				StrengthValue->SetVisibility(ESlateVisibility::Collapsed);
				StaminaValue->SetVisibility(ESlateVisibility::Collapsed);
				DefenseValue->SetVisibility(ESlateVisibility::Collapsed);

				Health->SetVisibility(ESlateVisibility::Collapsed);
				Defense->SetVisibility(ESlateVisibility::Collapsed);
				Stamina->SetVisibility(ESlateVisibility::Collapsed);
				Strength->SetVisibility(ESlateVisibility::Collapsed);

				//remove stamina
				StaminaRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				StaminaRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);

				//remove health
				HealthRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				HealthRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);


				break;

			case EItemType::Weapon:

				ItemType->SetText(FText::FromString("Weapon"));


				AttackPower->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.AttackPower));
				CriticalHit->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.CriticalHitRate));
				MagicPower->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.MagicPower));
				AttackSpeed->SetText(FText::AsNumber(ItemBeingHovered->ItemWeaponStatistics.AtttackSpeed));

				CharacterStatText->SetVisibility(ESlateVisibility::Collapsed);

				//Remove Character stats visibility
				HealthValue->SetVisibility(ESlateVisibility::Collapsed);
				StrengthValue->SetVisibility(ESlateVisibility::Collapsed);
				StaminaValue->SetVisibility(ESlateVisibility::Collapsed);
				DefenseValue->SetVisibility(ESlateVisibility::Collapsed);

				Health->SetVisibility(ESlateVisibility::Collapsed);
				Defense->SetVisibility(ESlateVisibility::Collapsed);
				Stamina->SetVisibility(ESlateVisibility::Collapsed);
				Strength->SetVisibility(ESlateVisibility::Collapsed);

				//remove stamina
				StaminaRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				StaminaRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);

				//remove health
				HealthRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				HealthRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);
				break;

			case EItemType::Netherband:


				Health->SetText(FText::AsNumber(ItemBeingHovered->ItemCharacerStatistics.Health));
				Defense->SetText(FText::AsNumber(ItemBeingHovered->ItemCharacerStatistics.Defense));
				Stamina->SetText(FText::AsNumber(ItemBeingHovered->ItemCharacerStatistics.Stamina));
				Strength->SetText(FText::AsNumber(ItemBeingHovered->ItemCharacerStatistics.Strength));

				WeaponStatText->SetVisibility(ESlateVisibility::Collapsed);

				//Remove WeaponStats visibility
				AttackPowerValue->SetVisibility(ESlateVisibility::Collapsed);
				CriticalHitValue->SetVisibility(ESlateVisibility::Collapsed);
				MagicPowerValue->SetVisibility(ESlateVisibility::Collapsed);
				AttackSpeedValue->SetVisibility(ESlateVisibility::Collapsed);

				AttackPower->SetVisibility(ESlateVisibility::Collapsed);
				CriticalHit->SetVisibility(ESlateVisibility::Collapsed);
				MagicPower->SetVisibility(ESlateVisibility::Collapsed);
				AttackSpeed->SetVisibility(ESlateVisibility::Collapsed);

				//remove stamina
				StaminaRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				StaminaRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);

				//remove health
				HealthRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				HealthRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);

				break;

			case EItemType::Spell:
				break;

			case EItemType::Consumable:
				ItemType->SetText(FText::FromString("Consumable"));

				StaminaRestorationAmountValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.StaminaRestorationAmount));
				HealthRestorationAmountValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.HealthRestorationAmount));


				WeaponStatText->SetVisibility(ESlateVisibility::Collapsed);

				//Remove WeaponStats visibility
				AttackPowerValue->SetVisibility(ESlateVisibility::Collapsed);
				CriticalHitValue->SetVisibility(ESlateVisibility::Collapsed);
				MagicPowerValue->SetVisibility(ESlateVisibility::Collapsed);
				AttackSpeedValue->SetVisibility(ESlateVisibility::Collapsed);

				AttackPower->SetVisibility(ESlateVisibility::Collapsed);
				CriticalHit->SetVisibility(ESlateVisibility::Collapsed);
				MagicPower->SetVisibility(ESlateVisibility::Collapsed);
				AttackSpeed->SetVisibility(ESlateVisibility::Collapsed);

				CharacterStatText->SetVisibility(ESlateVisibility::Collapsed);

				//Remove Character stats visibility
				HealthValue->SetVisibility(ESlateVisibility::Collapsed);
				StrengthValue->SetVisibility(ESlateVisibility::Collapsed);
				StaminaValue->SetVisibility(ESlateVisibility::Collapsed);
				DefenseValue->SetVisibility(ESlateVisibility::Collapsed);

				Health->SetVisibility(ESlateVisibility::Collapsed);
				Defense->SetVisibility(ESlateVisibility::Collapsed);
				Stamina->SetVisibility(ESlateVisibility::Collapsed);
				Strength->SetVisibility(ESlateVisibility::Collapsed);



				break;

			case EItemType::Quest:
				break;

			case EItemType::Mudane:
				ItemType->SetText(FText::FromString("Mundane Item"));

				//remove stamina
				StaminaRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				StaminaRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);

				//remove health
				HealthRestorationAmountText->SetVisibility(ESlateVisibility::Collapsed);
				HealthRestorationAmountValue->SetVisibility(ESlateVisibility::Collapsed);
				break;

			default:
				break;
			}

			//set all fields with item data.
			ItemName->SetText(ItemBeingHovered->ItemTextData.Name);
			UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);
			ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);


		}
	}
	
}
