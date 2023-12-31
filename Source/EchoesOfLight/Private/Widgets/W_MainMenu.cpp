// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_MainMenu.h"
#include "Character/MainCharacter.h"
#include "Widgets/DragItemVisual.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"

void UW_MainMenu::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	PlayerCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());

}

bool UW_MainMenu::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemDragDrop = Cast< UItemDragDropOperation>(InOperation);

	if (PlayerCharacter && ItemDragDrop->SourceItem)
	{
		PlayerCharacter->DropItem(ItemDragDrop->SourceItem, ItemDragDrop->SourceItem->Quantity);
		return true;
	}
	return false;

}
