// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_EquipmentSlot.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"
#include "Widgets/DragItemVisual.h"

//engine
#include "Components/Image.h"  
#include "Components/Border.h"
#include "Components/TextBlock.h"


void UW_EquipmentSlot::NativeConstruct()
{
	Super::NativeConstruct();

}

bool UW_EquipmentSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	const UItemDragDropOperation* ItemBeingDroppedOnWidget = Cast<UItemDragDropOperation>(InOperation);

	if (ItemBeingDroppedOnWidget->SourceItem)
	{
		ItemReference = ItemBeingDroppedOnWidget->SourceItem;

		if (ItemReference)
		{
			ItemBeingDroppedOnWidget->SourceInventory->RemoveSingleInstanceOfItem(ItemBeingDroppedOnWidget->SourceItem);
			if (EquipmentIcon)
			{
				EquipmentIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
				EquipmentIcon->SetVisibility(ESlateVisibility::Visible);
				UE_LOG(LogTemp, Warning, TEXT("Equipment Icon is present"))
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("No equipment ICon"))
			}
			return true;
		}

	}



	return false;
}

FReply UW_EquipmentSlot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply Reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		return Reply.Handled().DetectDrag(TakeWidget(), EKeys::LeftMouseButton);
	}

	//sub menu on right click happens here.

	return Reply.Unhandled();
}

void UW_EquipmentSlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (DragItemVisualClass && ItemReference)
	{
		// Create widget
		const TObjectPtr<UDragItemVisual> DragVisual = CreateWidget<UDragItemVisual>(this, DragItemVisualClass);

		//set visuals of drag widget.
		DragVisual->ItemIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		DragVisual->ItemBorder->SetBrushColor(DragVisual->ItemBorder->GetBrushColor());
		DragVisual->ItemQuantity->SetText(FText::AsNumber(ItemReference->Quantity));

		//creates a object out of the dragged Item
		UItemDragDropOperation* DragItemOperation = NewObject<UItemDragDropOperation>();

		// gives the dragged object the reference to the item clicked on in inventory.
		DragItemOperation->SourceItem = ItemReference;

		// give the dragged object reference to the player inventory.
		DragItemOperation->SourceInventory = ItemReference->OwningInventory;

		//set the drag visual.
		DragItemOperation->DefaultDragVisual = DragVisual;

		DragItemOperation->EquipmentSlotReference = this;

		EquipmentIcon->SetVisibility(ESlateVisibility::Hidden);

		//set where the dragged item icon is attached to the mouse when dragging.
		DragItemOperation->Pivot = EDragPivot::MouseDown;
		OutOperation = DragItemOperation;

		//ItemReference = nullptr;

		//EquipmentIcon = nullptr;

	}
}

void UW_EquipmentSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	const UItemDragDropOperation* ItemBeingDroppedOnWidget = Cast<UItemDragDropOperation>(InOperation);

	if (ItemBeingDroppedOnWidget->SourceItem)
	{
		ItemReference = ItemBeingDroppedOnWidget->SourceItem;

		EquipmentIcon->SetVisibility(ESlateVisibility::Visible);
	}
}
