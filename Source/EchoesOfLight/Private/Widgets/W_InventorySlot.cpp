// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_InventorySlot.h"
#include "Libraries/BFL_Utility.h"
#include "Components/Image.h"


void UW_InventorySlot::SetItem(const FDataTableRowHandle& InSlotItem)
{
	SlotItem = InSlotItem;
}

void UW_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	Texture = Utility->BPL_GetItemInfo(SlotItem).Picture;

	InventorySlotImage->SetBrushFromTexture(Texture);

}

