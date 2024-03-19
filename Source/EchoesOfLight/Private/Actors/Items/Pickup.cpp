// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Items/Pickup.h"
#include "Actors/Items/ItemBase.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_Inventory.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	PickupMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pickup Mesh"));

	PickupMesh->SetSimulatePhysics(true); 

	SetRootComponent(PickupMesh);

}


// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();

	InitializePickup(ItemQuantity);

}

void APickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	//check that the name is valid
	const FName ChangedPropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangedPropertyName == GET_MEMBER_NAME_CHECKED(APickup, DesiredItemId))
	{
		if (ItemDataTable)
		{
			if (const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(DesiredItemId, DesiredItemId.ToString()))
			{
				PickupMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);
			}

		}
	}
}

void APickup::InitializePickup(const int32 InQuantity)
{
	//check to see if the data table is set and the desired item is name is set
	if (ItemDataTable && !DesiredItemId.IsNone())
	{
		//get the item info from the data table.
		const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(DesiredItemId, DesiredItemId.ToString());

		//create a new item
		ItemReference = NewObject<UItemBase>(this, UItemBase::StaticClass());

		//set the item properties
		ItemReference->ID = ItemDataRow->ID;
		ItemReference->ItemType = ItemDataRow->ItemType;
		ItemReference->ItemQuality = ItemDataRow->ItemQuality;
		ItemReference->ItemNumericaData = ItemDataRow->ItemNumericaData;
		ItemReference->ItemTextData = ItemDataRow->ItemTextData;
		ItemReference->ItemAssetData = ItemDataRow->ItemAssetData;
		ItemReference->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
		ItemReference->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

		//set the desired quantity based off the passed in data.
		InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

		// set item mesh
		PickupMesh->SetStaticMesh(ItemDataRow->ItemAssetData.Mesh);

		// update interaction widget data

		UpdateInteractableData();
	};
}

void APickup::UpdateInteractableData()
{
	InstanceInteractableData.InteractableType = EInteractableType::Pickup;
	InstanceInteractableData.Action = ItemReference->ItemTextData.InteractionText;
	InstanceInteractableData.Name = ItemReference->ItemTextData.Name;
	InstanceInteractableData.Quantity = ItemReference->Quantity;
	InteractableData = InstanceInteractableData;


}



void APickup::InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity)
{
	ItemReference = ItemToDrop;
	InQuantity <= 0 ? ItemReference->SetQuantity(1) : ItemReference->SetQuantity(InQuantity);

	ItemReference->ItemNumericaData.Weight = ItemToDrop->GetItemSingleWeight();

	PickupMesh->SetStaticMesh(ItemToDrop->ItemAssetData.Mesh);

	UpdateInteractableData();
}


/*Interaction Interface*/

void APickup::BeginFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(true);
	}
}

void APickup::EndFocus()
{
	if (PickupMesh)
	{
		PickupMesh->SetRenderCustomDepth(false);
	}
}

void APickup::Interact(AMainCharacter* PlayerCharacter)
{
	if (PlayerCharacter)
	{
		TakePickup(PlayerCharacter);
	}
}

/*END*/


void APickup::TakePickup(const AMainCharacter* Taker)
{
	//check wether the item is not pending destruction
	if (!IsPendingKillPending())
	{
		if (ItemReference && Taker)
		{
			if(UAC_Inventory* PlayerInventory = Taker->GetInventory())
			{
				const FItemAddResult AddResult = PlayerInventory->HandleAddItem(ItemReference);

				switch (AddResult.OperationResult)
				{
				case EItemAddResult::IAR_NoItemAdded:
					break;

				case EItemAddResult::IAR_PartialAmountItemAdded:
					UpdateInteractableData();
					//Updates the UI interaction widget with the data.
					Taker->UpdateInteractionWidget();
					//destroys item in the world (May need to change later)
					this->Destroy();
					break;

				case EItemAddResult::IAR_AllItemAdded:
					//destroys item in the world (May need to change later)
					this->Destroy();
					break;

				default:
					break;
				}

				UE_LOG(LogTemp, Warning, TEXT("%s"), *AddResult.ResultMessage.ToString())
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Player Inventory Component is null"))
			}

		
		}
		else 
		{
			UE_LOG(LogTemp, Warning, TEXT("Pickup internal item reference was somehow null!"))
		}
	}
}

