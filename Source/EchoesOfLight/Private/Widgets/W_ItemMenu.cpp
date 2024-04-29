// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_ItemMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Actors/Items/ItemBase.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_EquipmentMenu.h"
#include "Widgets/W_EquipmentSlot.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Widgets/W_InventoryPanel.h"
#include "Enums/Enums.h"

void UW_ItemMenu::NativeOnInitialized()
{
	bIsFocusable = true;

	UseButton->OnClicked.AddDynamic(this, &UW_ItemMenu::UseItem);
	EquipButton->OnClicked.AddDynamic(this, &UW_ItemMenu::Equip);
	DeleteButton->OnClicked.AddDynamic(this, &UW_ItemMenu::Delete);

	EquipButton->SetVisibility(ESlateVisibility::Collapsed);
	EquipButtonText->SetVisibility(ESlateVisibility::Collapsed);
	
}

void UW_ItemMenu::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	RemoveFromViewport();
}

void UW_ItemMenu::UseItem()
{
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (item && character)
	{
		item->Use(character);
		UE_LOG(LogTemp, Warning, TEXT("UseItem Called"))


	}

}

void UW_ItemMenu::Equip()
{
	AMainCharacter* character = Cast<AMainCharacter>(GetOwningPlayerPawn());
	if (item && character)
	{
		character->EquipEquipment(item);
		character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->RefreshInventory();
		UE_LOG(LogTemp, Warning, TEXT("Equip Called"))
	}
}

void UW_ItemMenu::Delete()
{
	if (AMainCharacter* character = Cast<AMainCharacter>(GetOwningPlayerPawn()))
	{
		if (item->ItemNumericaData.bisStackable)
		{
			character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->InventoryReference->RemoveAmountOfItem(item, item->ItemNumericaData.MaxStackSize);
			character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->RefreshInventory();
			UE_LOG(LogTemp, Warning, TEXT("delete Called amount specified"))
		}
		else 
		{
			character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->InventoryReference->RemoveSingleInstanceOfItem(item);
			character->MainWidgetHandlerComponent->EquipmentMenuWidget->InventoryWidget->RefreshInventory();
			UE_LOG(LogTemp, Warning, TEXT("delete Called single instance"))
		}
		
	}
}
