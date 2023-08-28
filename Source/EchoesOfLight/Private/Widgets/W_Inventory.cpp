// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_Inventory.h"
#include "Components/UniformGridPanel.h"
#include "Components/UniformGridSlot.h"
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
	CurrentColumn = 0;
	CurrentRow = 0;

	if (InventoryGrid)
	{
		InventoryGrid->ClearChildren();
	}
	UAC_Inventory* Inventory = Cast<UAC_Inventory>(GetOwningPlayer()->GetPawn()->GetComponentByClass(AC_Inventory));

	if (Inventory)
	{
		for (int item = 0; item < Inventory->Inventory.Num(); item++)
		{
			UW_InventorySlot* SlotWidget = CreateWidget<UW_InventorySlot>(GetOwningPlayer(), InventorySlot);

			// Set the item for the slot
			if (SlotWidget)
			{
				SlotWidget->SetItem(Inventory->Inventory[item]);

				// Add the slot to the grid or any other container
				UUniformGridSlot* GridSlot = InventoryGrid->AddChildToUniformGrid(SlotWidget, CurrentRow, CurrentColumn);

				if (GridSlot)
				{
					GridSlot->SetRow(CurrentRow);
					GridSlot->SetColumn(CurrentColumn);
					
				}
			}
			CalculateNewColumnAndRow();

		}
		
	}
}

void UW_Inventory::CalculateNewColumnAndRow()
{
	if ((CurrentColumn + 1) > (MaxNumberOfColumns - 1))
	{
		CurrentColumn = 0;
		CurrentRow += 1;
	}
	else
	{
		CurrentColumn += 1;
	}

}
