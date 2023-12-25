// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_Inventory.h"
#include "Widgets/W_InventorySlot.h"
#include "Actors/Items/Item.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "ActorComponents/AC_Inventory.h"
#include "Widgets/W_InventorySlot.h"

void UW_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	Update.AddDynamic(this, &UW_Inventory::OnUpdate);
	Update.Broadcast();

}

void UW_Inventory::OnUpdate()
{
}

//Adds item to the Inventory widget and sets image and reference to the item.
void UW_Inventory::AddItemToInventoryWidget(AItem* Item)
{
	//Checks if the inventory has space
	if (bIsInventoryFull == false)
	{
		//Finds the closest open index
		Index = FindOpenSlot();

		//check that the index is inbounds and pointers are not null.
		if (InventoryGrid && Item && Index >= 0 && bIsInventoryFull == false)
		{
			//cast the slot to the inventory slot class
			UW_InventorySlot* CurrentSlot = Cast<UW_InventorySlot>(InventoryGrid->GetChildAt(Index));
			if (CurrentSlot)
			{
				//Sets the reference, item picture, hasItem, and Index on grid.
				CurrentSlot->setItemInSlot(Item);
				CurrentSlot->SetItemIconImage(Item->ItemInfo.Picture);
				CurrentSlot->ItemInslot->indexInInventoryGrid = Index;
				CurrentSlot->bHasItem = true;
			}
		}

	}
}


//Finds a open slot on the inventory widget and returns -1 if the no slot was found.
int32 UW_Inventory::FindOpenSlot()
{
	int32 newIndex = 0;

	// iterates through each slot in the grid till one is found that has not been uses.
	for (int32 i = 0; i < InventoryGrid->GetChildrenCount(); i++)
	{
		UW_InventorySlot* CurrentSlot = Cast<UW_InventorySlot>(InventoryGrid->GetChildAt(i));
		if (CurrentSlot)
		{
			if (CurrentSlot->bHasItem == false)
			{
				newIndex = i;

				return newIndex;
			}
		}
		else
		{
			newIndex = -1;
		}
	}
	//After the iteration and no index is found. The inventory is full and set the boolean value is set accordingly.
	if (newIndex == -1)
	{
		bIsInventoryFull = true;
	}


	return newIndex;
}

//Removes an item from the Inventory widget.
void UW_Inventory::RemoveItemFromInventoryWidget(AItem* Item)
{
	if (Item)
	{
		//get Inventory slot at its location
		UW_InventorySlot* CurrentSlot = Cast<UW_InventorySlot>(InventoryGrid->GetChildAt(Item->indexInInventoryGrid));
		if (CurrentSlot)
		{
			//remove the Picture, set has item to fasle and remove the reference to the Item.
			CurrentSlot->Texture = nullptr;
			CurrentSlot->bHasItem = false;
			CurrentSlot->ItemInslot = nullptr;
		}
	}
}

