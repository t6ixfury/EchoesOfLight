// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"

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
	//implement later
}
