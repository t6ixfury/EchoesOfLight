// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_InventorySlot.h"
#include "Actors/Items/ItemBase.h"
#include "Widgets/InventoryToolTip.h"
#include "Widgets/DragItemVisual.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Widgets/W_ItemMenu.h"

//engine
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"




void UW_InventorySlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ToolTipClass)
	{
		UInventoryToolTip* ToolTip = CreateWidget<UInventoryToolTip>(this, ToolTipClass);
		ToolTip->InventorySlotBeingHovered = this;

		SetToolTip(ToolTip);
	};
}

void UW_InventorySlot::NativeConstruct()
{
	Super::NativeConstruct();

	if (ItemReference)
	{
		
		//set Item icon image
		ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		
		//if item is stackable, update quantity.
		if (ItemReference->ItemNumericaData.bisStackable)
		{
			ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));
		}
		else
		{
			//if not stackable, hide quantity.
			ItemQuantity->SetVisibility(ESlateVisibility::Collapsed);
		}
	}

}

FReply UW_InventorySlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	//sub menu on right click happens here.
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		UW_ItemMenu* ItemMenu = CreateWidget<UW_ItemMenu>(this, RightClickMenuClass);
		if (ItemMenu)
		{
			ItemMenu->item = ItemReference;

			// Set the position of the menu at the mouse cursor
			const FVector2D CursorPos = InMouseEvent.GetLastScreenSpacePosition();
			ItemMenu->SetPositionInViewport(CursorPos, true);

			// Add the widget to the viewport if needed
			ItemMenu->AddToViewport(15);

			ItemMenu->SetFocus();

			return FReply::Handled();
		}
	}
	
	return Reply.Unhandled();


}

void UW_InventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
}

void UW_InventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragItemVisualClass && ItemReference)
	{
		// Create widget
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget< UDragItemVisual>(this, DragItemVisualClass);

		//set visuals of drag widget.
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

		//creates a object out of the dragged Item
		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();

		// gives the dragged object the reference to the item clicked on in inventory.
		DragItemOperation->SourceItem = ItemReference;

		// give the dragged object reference to the player inventory.
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		//set the drag visual.
		DragItemOperation->DefaultDragVisual = DragVisual;

		//set where the dragged item icon is attached to the mouse when dragging.
		DragItemOperation->Pivot = EDragPivot::MouseDown;
		OutOperation = DragItemOperation;

	}
}

bool UW_InventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

