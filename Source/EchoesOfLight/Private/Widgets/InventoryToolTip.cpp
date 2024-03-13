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
				break;

			case EItemType::Weapon:
				break;

			case EItemType::Netherband:
				break;

			case EItemType::Spell:
				break;

			case EItemType::Consumable:
				ItemType->SetText(FText::FromString("Consumable"));
				DamageValue->SetVisibility(ESlateVisibility::Collapsed);
				ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
				SellValue->SetVisibility(ESlateVisibility::Collapsed);
				break;

			case EItemType::Quest:
				break;

			case EItemType::Mudane:
				ItemType->SetText(FText::FromString("Mundane Item"));
				DamageValue->SetVisibility(ESlateVisibility::Collapsed);
				ArmorRating->SetVisibility(ESlateVisibility::Collapsed);
				UsageText->SetVisibility(ESlateVisibility::Collapsed);
				SellValue->SetVisibility(ESlateVisibility::Collapsed);
				break;

			default:
				break;
			}

			//set all fields with item data.
			ItemName->SetText(ItemBeingHovered->ItemTextData.Name);
			DamageValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.DamageValue));
			ArmorRating->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.ArmorRating));
			UsageText->SetText(ItemBeingHovered->ItemTextData.UsageText);
			ItemDescription->SetText(ItemBeingHovered->ItemTextData.Description);
			StackWeight->SetText(FText::AsNumber(ItemBeingHovered->GetItemSingleWeight()));
			SellValue->SetText(FText::AsNumber(ItemBeingHovered->ItemStatistics.SellValue));


			if (ItemBeingHovered->ItemNumericaData.bisStackable)
			{
				MaxStackSize->SetText(FText::AsNumber(ItemBeingHovered->ItemNumericaData.MaxStackSize));
			}
			else
			{
				MaxStackSize->SetVisibility(ESlateVisibility::Collapsed);
			}


		}
	}
	
}
