// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_InventoryPanel.h"
#include <Character/MainCharacter.h>
#include <ActorComponents/AC_Inventory.h>
#include "Widgets/W_InventorySlot.h"
#include "Widgets/ItemDragDropOperation.h"

//engine
#include <Components/WrapBox.h>
#include <Components/TextBlock.h>





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

	if (ItemDragDrop->SourceItem && InventoryReference)
	{
		// returning true will stop the drop operation at this widget.
		return true;
	}
	//returning false will cause the drop operation to fall through to underlying widgets.
	return false;
}


