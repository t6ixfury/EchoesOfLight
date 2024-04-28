// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_EquipmentSlot.h"
#include "Widgets/ItemDragDropOperation.h"
#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"
#include "Widgets/DragItemVisual.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_EquipmentMenu.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Widgets/W_InventoryPanel.h"

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

	if (ItemBeingDroppedOnWidget->SourceItem->ItemType == EquipmentType)
	{
		AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(GetOwningPlayerPawn());
		if (ItemReference && PlayerCharacter)
		{

			ItemBeingDroppedOnWidget->SourceInventory->HandleAddItem(ItemReference);
			
			PlayerCharacter->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->WasEquipmentAddedToInventory(EquipmentType, ItemReference);
			ItemReference = nullptr;
		}

		if(ItemReference == nullptr)
		{
			ItemReference = ItemBeingDroppedOnWidget->SourceItem;
		}

		if (ItemReference)
		{
			UE_LOG(LogTemp, Warning, TEXT("Equipment slot: Strength: %d, Stamina: %d"), ItemReference->ItemCharacerStatistics.Strength, ItemReference->ItemCharacerStatistics.Stamina)

			SlotItemId = ItemReference->ID;

			EItemType EquipmentResult = EventItemEquipped(ItemReference->ItemType, ItemReference);

			//Remove the now equipped equipment item from inventory.
			ItemBeingDroppedOnWidget->SourceInventory->RemoveSingleInstanceOfItem(ItemBeingDroppedOnWidget->SourceItem);

			//set the icon image for the equipment slot and set to visisble.
			EquipmentIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
			EquipmentIcon->SetVisibility(ESlateVisibility::Visible);
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
		
		//sets the visibilty of the Icon to hidden so the slot appears blank.
		EquipmentIcon->SetVisibility(ESlateVisibility::Hidden);

		//set where the dragged item icon is attached to the mouse when dragging.
		DragItemOperation->Pivot = EDragPivot::MouseDown;
		OutOperation = DragItemOperation;

	}
}

void UW_EquipmentSlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	const UItemDragDropOperation* ItemBeingDroppedOnWidget = Cast<UItemDragDropOperation>(InOperation);

	if (ItemBeingDroppedOnWidget->SourceItem)
	{
		//might delete later. redudant.
		ItemReference = ItemBeingDroppedOnWidget->SourceItem;
		SlotItemId = ItemBeingDroppedOnWidget->SourceItem->ID;
		//set the visibilty of the icon to visible since the equipment was not removed.
		EquipmentIcon->SetVisibility(ESlateVisibility::Visible);
	}
}

void UW_EquipmentSlot::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

EItemType  UW_EquipmentSlot::EventItemEquipped(EItemType EquipmentTypeToBeHandled, UItemBase* ItemRef)
{
	switch (EquipmentTypeToBeHandled)
	{
	case EItemType::Amulet:
		AmuletChange.Broadcast();

		return EItemType::Amulet;
		break;
	case EItemType::Weapon:
		WeaponChange.Broadcast();

		return EItemType::Weapon;
		break;
	case EItemType::Netherband:

		NetherBandChange.Broadcast();
		return EItemType::Netherband;
		break;
	default:
		return EItemType::Mudane;
		break;
	}
}

void UW_EquipmentSlot::SetIconImage()
{
	
	if (ItemReference->ItemAssetData.Icon)
	{
		EquipmentIcon->SetBrushFromTexture(ItemReference->ItemAssetData.Icon);
		EquipmentIcon->SetVisibility(ESlateVisibility::Visible);
	}

}

void UW_EquipmentSlot::CreateItem(UDataTable* table, FName DesiredItemId )
{
	if (table && !DesiredItemId.IsNone())
	{
		//get the item info from the data table.
		const FItemData* ItemDataRow = table->FindRow<FItemData>(DesiredItemId, DesiredItemId.ToString());

		UItemBase* newItem = NewObject<UItemBase>(this, UItemBase::StaticClass());
		//create a new item
		ItemReference = NewObject<UItemBase>(this, UItemBase::StaticClass());

		//set the item properties
		newItem->ID = ItemDataRow->ID;
		newItem->ItemType = ItemDataRow->ItemType;
		newItem->ItemQuality = ItemDataRow->ItemQuality;
		newItem->ItemNumericaData = ItemDataRow->ItemNumericaData;
		newItem->ItemTextData = ItemDataRow->ItemTextData;
		newItem->ItemAssetData = ItemDataRow->ItemAssetData;
		newItem->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
		newItem->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;
		newItem->SetQuantity(1);

		ItemReference = newItem;


	};
}


UItemBase* UW_EquipmentSlot::GetItemReference()
{
	if (ItemReference)
	{
		return ItemReference;
	}
	UE_LOG(LogTemp, Warning, TEXT("EQuipment slot is null"))
	return nullptr;
}
