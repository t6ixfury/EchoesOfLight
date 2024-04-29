// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Widgets/W_EquipmentMenu.h"
#include "Widgets/W_EquipmentSlot.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "Widgets/W_InventoryPanel.h"

UItemBase::UItemBase() : bIsCopy(false), bIsPickup(false)
{
}

void UItemBase::ResetItemFlags()
{
	bIsCopy = false;
	bIsPickup = false;
}

UItemBase* UItemBase::CreateItemCopy() const
{
	UItemBase* ItemCopy = NewObject<UItemBase>(StaticClass());
	ItemCopy->ID = this->ID;
	ItemCopy->Quantity = this->Quantity;
	ItemCopy->ItemQuality = this->ItemQuality;
	ItemCopy->ItemType = this->ItemType;
	ItemCopy->ItemTextData = this->ItemTextData;
	ItemCopy->ItemNumericaData = this->ItemNumericaData;
	ItemCopy->ItemStatistics = this->ItemStatistics;
	ItemCopy->ItemAssetData = this->ItemAssetData;
	ItemCopy->ItemWeaponStatistics = this->ItemWeaponStatistics;
	ItemCopy->ItemCharacerStatistics = this->ItemCharacerStatistics;
	ItemCopy->bIsCopy = true;


	return ItemCopy;


}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
	if (NewQuantity != Quantity)
	{
		Quantity = FMath::Clamp(NewQuantity, 0, ItemNumericaData.bisStackable ? ItemNumericaData.MaxStackSize : 1);
		
		if (OwningInventory)
		{
			if (Quantity <= 0)
			{
				OwningInventory->RemoveSingleInstanceOfItem(this);
			}
		}
		
	}
}

void UItemBase::Use(AMainCharacter* Character)
{
	if (Character)
	{
		switch (ItemType)
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

			Character->DamageSystem->Heal(ItemStatistics.HealthRestorationAmount);
			Character->CurrentStamina = FMath::Clamp((Character->CurrentStamina + ItemStatistics.StaminaRestorationAmount), 0, Character->Stamina);
			Character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->InventoryReference->RemoveSingleInstanceOfItem(this);
			break;

		case EItemType::Quest:
			break;

		case EItemType::Mudane:

			break;
		}
	}
}


FItemSaveInfo UItemBase::SaveItem(UItemBase* item)
{
	FItemSaveInfo info;

	info.ID = item->ID;
	info.ItemAssetData = item->ItemAssetData;
	info.ItemCharacerStatistics = item->ItemCharacerStatistics;
	info.ItemNumericaData = item->ItemNumericaData;
	info.ItemQuality = item->ItemQuality;
	info.ItemStatistics = item->ItemStatistics;
	info.ItemTextData = item->ItemTextData;
	info.ItemType = item->ItemType;
	info.ItemWeaponStatistics = item->ItemWeaponStatistics;
	info.Quantity = item->Quantity;

	return info;
}
