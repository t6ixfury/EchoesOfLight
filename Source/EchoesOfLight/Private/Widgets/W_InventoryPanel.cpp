// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_InventoryPanel.h"
#include <Character/MainCharacter.h>
#include <ActorComponents/AC_Inventory.h>
#include "Widgets/W_InventorySlot.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Widgets/W_EquipmentSlot.h"
#include "Actors/Items/ItemBase.h"

//engine
#include <Components/WrapBox.h>
#include <Components/TextBlock.h>
#include "Components/Image.h"  





void UW_InventoryPanel::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlayerCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());

	if (PlayerCharacter)
	{
		InventoryReference = PlayerCharacter->GetInventory();

		if (InventoryReference)
		{
			InventoryReference->OnInventoryUpdated.AddUObject(this, &UW_InventoryPanel::RefreshInventory);
			SetInfoText();
		}
	}
}

void UW_InventoryPanel::SetInfoText() const
{
	WeightInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), InventoryReference->GetInventoryTotalWeight(), InventoryReference->GetWeightCapacity()));

	CapacityInfo->SetText(FText::Format(FText::FromString("{0}/{1}"), InventoryReference->GetInventoryContents().Num(), InventoryReference->GetSlotsCapacity()));
}

void UW_InventoryPanel::RefreshInventory()
{
	if (InventoryReference && InventorySlotClass)
	{
		//remove all items in the inventory ui
		InventoryPanel->ClearChildren();

		//loop through each item in the inventory.
		for (UItemBase* const& InventoryItem : InventoryReference->GetInventoryContents())
		{
			//create the inventoryslot widget
			UW_InventorySlot* ItemSlot = CreateWidget<UW_InventorySlot>(this, InventorySlotClass);
			ItemSlot->SetItemReference(InventoryItem);

			//attach inventory slot widget to the wrapbox
			InventoryPanel->AddChildToWrapBox(ItemSlot);
		}

		SetInfoText();
	}
}

bool UW_InventoryPanel::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast<UItemDragDropOperation>(InOperation);

	//checks for null ptrs and If the Item being dropped on the inventory is not the same item picked up.
	if (ItemDragDrop->SourceItem && InventoryReference && !InventoryReference->FindMatchingItem(ItemDragDrop->SourceItem))
	{
		
		FItemAddResult Result = InventoryReference->HandleAddItem(ItemDragDrop->SourceItem);
		
		//check to see if the item was indeed added to the inventory
		if (Result.OperationResult == EItemAddResult::IAR_AllItemAdded)
		{
			if (ItemDragDrop->EquipmentSlotReference->ItemReference)
			{
				WasEquipmentAddedToInventory(ItemDragDrop->EquipmentSlotReference->EquipmentType, ItemDragDrop->EquipmentSlotReference->ItemReference);
				//remove the reference to the item currently in the equipment slot.
				ItemDragDrop->EquipmentSlotReference->ItemReference = nullptr;
				return true;
			}
		}
	}
	//returning false will cause the drop operation to fall through to underlying widgets.
	return false;
}

void UW_InventoryPanel::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);


}

void UW_InventoryPanel::WasEquipmentAddedToInventory(EItemType EquipmentType, UItemBase* EquipmentItem)
{
	switch (EquipmentType)
	{
	case EItemType::Amulet:
		break;
	case EItemType::Weapon:
		//Removes the weapon that was previously in slot.
		PlayerCharacter->OnWeaponSlotRemoval();
		break;
	case EItemType::Netherband:
		PlayerCharacter->NetherbandUnEquipped(EquipmentItem);
		break;
	default:
		break;
	}
}


