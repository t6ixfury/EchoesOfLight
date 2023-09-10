// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_Inventory.h"
#include "Engine/DataTable.h"
#include "Save/Save_Inventory.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_Inventory.h"
#include "Kismet/GameplayStatics.h"
#include "Save/Save_Inventory.h"

// Sets default values for this component's properties
UAC_Inventory::UAC_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	

	// ...
}


// Called when the game starts
void UAC_Inventory::BeginPlay()
{
	Super::BeginPlay();
	LoadInventory();
	
}


// Called every frame
void UAC_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_Inventory::AddItems(TArray<FDataTableRowHandle> items)
{
	for (int item = 0; item < items.Num(); item++)
	{
		Inventory.Add(items[item]);
	}
	UpdateInventory();
}

void UAC_Inventory::UpdateInventory()
{
	if (MainCharacter)
	{
		if (InventoryWidget)
		{
			InventoryWidget->Update.Broadcast();
		}

	}
}

void UAC_Inventory::SaveInventory()
{
	if (UGameplayStatics::DoesSaveGameExist(InventorySlot, 0))
	{
		USave_Inventory* InventoryInfo = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventorySlot, 0));
		if (InventoryInfo)
		{
			SaveGame = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventorySlot, 0));
			Inventory = InventoryInfo->sInventory;
		}
		else
		{
			USave_Inventory* Save;
			SaveGame = Cast<USave_Inventory>(UGameplayStatics::CreateSaveGameObject(Save->StaticClass()));
		}
	}
}

void UAC_Inventory::LoadInventory()
{
	if (UGameplayStatics::DoesSaveGameExist(InventorySlot, 0))
	{
		USave_Inventory* InventoryInfo = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventorySlot, 0));
		if (InventoryInfo)
		{
			Inventory = InventoryInfo->sInventory;
		}
	}
}

void UAC_Inventory::IntializePlayerEvent(UW_Inventory* InventoryToSet)
{
	InventoryWidget = InventoryToSet; // the problem is here. Nothing is calling this function to set the inventory widget
	MainCharacter = Cast<AMainCharacter>(GetOwner());
	if (MainCharacter->GetController())
	{
		CharacterController = Cast<APlayerController>(MainCharacter->GetController());
	}


}

void UAC_Inventory::ToggleInventory()
{
	if (InventoryWidget)
	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory Widget present"));

		if (InventoryWidget->GetVisibility() == ESlateVisibility::Visible)
		{
			InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
			if (CharacterController)
			{
				FInputModeGameOnly InputModeData;
				CharacterController->SetInputMode(InputModeData);
				CharacterController->bShowMouseCursor = false;
			}
			else
			{
				InventoryWidget->SetVisibility(ESlateVisibility::Visible);
				if (CharacterController)
				{
					FInputModeGameAndUI InputModeData;
					InputModeData.SetHideCursorDuringCapture(true);
					InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
					InputModeData.SetHideCursorDuringCapture(true);
					InputModeData.SetWidgetToFocus(InventoryWidget->TakeWidget());
					CharacterController->SetInputMode(InputModeData);
					CharacterController->bShowMouseCursor = true;
				}

			}

		}

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Inventory Widget not present"));
	}
}

