// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_InventorySlot.h"
#include "Actors/Items/Item.h"
#include "Components/Image.h"



void UW_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	InventorySlotImage->SetBrushFromTexture(Texture);

}

void UW_InventorySlot::SetItemIconImage(UTexture2D* TextureToSet)
{
	if (TextureToSet)
	{
		Texture = TextureToSet;

	}
}

void UW_InventorySlot::setItemInSlot(AItem* ItemToSet)
{
	if (ItemToSet)
	{
		ItemInslot = ItemToSet;
	}
}

