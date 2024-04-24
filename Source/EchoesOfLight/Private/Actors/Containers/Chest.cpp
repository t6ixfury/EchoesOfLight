// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Actors/Containers/Chest.h"
#include "Actors/Items/Pickup.h"
#include "Actors/Items/ItemBase.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_Inventory.h"

//engine
#include "Engine/World.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Components/BoxComponent.h"
#include "Animation/AnimInstance.h"







// Sets default values
AChest::AChest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SetRootComponent(SkeletalMesh);

	// Create the audio box component
	AudioBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Audio Trigger"));
	AudioBox->SetupAttachment(RootComponent);

	// Create the audio component
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));
	AudioComponent->SetupAttachment(RootComponent);




	SetDataTables();



}

void AChest::SetChestIsOpen()
{
	bIsChestOpen = true;
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_OpenChest);
	}
}

// Called when the game starts or when spawned
void AChest::BeginPlay()
{
	Super::BeginPlay();

	if (AudioComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("audio component here."))
	}

	AudioBox->OnComponentBeginOverlap.AddDynamic(this, &AChest::PlayChestAmbientAudio);
	AudioBox->OnComponentEndOverlap.AddDynamic(this, &AChest::StopChestAmbientAudio);

	UpdateInteractableData();


}

// Called every frame
void AChest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AChest::Interact(AMainCharacter* PlayerCharacter)
{
	if (bIsChestLootable)
	{
		//get the animinstance
		USkeletalMeshComponent* MeshComp = FindComponentByClass<USkeletalMeshComponent>();
		UAnimInstance* CharacterAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

		
		if (PlayerCharacter == nullptr)
		{
			return;
		}
		// if the chest open montage is set and the animinstance is not null  play the montage  and set timer to change the bIschestOpen variable
		//to true for then animation blueprint.
		if (ChestOpen && CharacterAnimInstance)
		{
			StopChestAudio();
			float montageDuration = CharacterAnimInstance->Montage_Play(ChestOpen) - 0.5f;
			GetWorldTimerManager().SetTimer(TimerHandle_OpenChest, this, &AChest::SetChestIsOpen, montageDuration, false);
		}
		//add items in the chest to the players inventory.
		for (FChestItemData ChestItem : ItemsToAddToChest)
		{
			PlayerCharacter->PlayerInventory->HandleAddItem(CreateItem(&ChestItem));
		}

		ChestOpenedDelegate.Broadcast(this);

		//flag to make the chess only lootable once.
		bIsChestLootable = false;
	}
	
}


void AChest::UpdateInteractableData()
{
	InteractableData.InteractableType = EInteractableType::Container;
	InteractableData.Name = FText::FromString(FString(TEXT("chest")));
	InteractableData.Action = FText::FromString(FString(TEXT("open")));
}

UItemBase* AChest::CreateItem(FChestItemData* ItemDataForCreation)
{
	
	if(ItemDataForCreation == nullptr)
	{ 
		return nullptr;
	}
	//Depending on the item type. Get the appropriate dataTable information for the item and then create the item.
	switch (ItemDataForCreation->ItemType)
	{
	case EItemType::Mudane:
		//check to see if the data table is set and the desired item is name is set
		if (ItemMundaneDataTable && !ItemDataForCreation->DesiredItemId.IsNone())
		{
			//get the item info from the data table.
			const FItemData* ItemDataRow = ItemMundaneDataTable->FindRow<FItemData>(ItemDataForCreation->DesiredItemId, ItemDataForCreation->DesiredItemId.ToString());

			//create a new item
			UItemBase* ItemToAdd = NewObject<UItemBase>(this, UItemBase::StaticClass());

			//set the item properties
			ItemToAdd->ID = ItemDataRow->ID;
			ItemToAdd->ItemType = ItemDataRow->ItemType;
			ItemToAdd->ItemQuality = ItemDataRow->ItemQuality;
			ItemToAdd->ItemNumericaData = ItemDataRow->ItemNumericaData;
			ItemToAdd->ItemTextData = ItemDataRow->ItemTextData;
			ItemToAdd->ItemAssetData = ItemDataRow->ItemAssetData;
			ItemToAdd->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
			ItemToAdd->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

			//set the desired quantity based off the passed in data.
			ItemDataForCreation->DesiredQuantiy <= 0 ? ItemToAdd->SetQuantity(1) : ItemToAdd->SetQuantity(ItemDataForCreation->DesiredQuantiy);

			return ItemToAdd;
		}
		break;
	
	case EItemType::Amulet:
		//check to see if the data table is set and the desired item is name is set
		if (ItemAmuletDataTable && !ItemDataForCreation->DesiredItemId.IsNone())
		{
			//get the item info from the data table.
			const FItemData* ItemDataRow = ItemAmuletDataTable->FindRow<FItemData>(ItemDataForCreation->DesiredItemId, ItemDataForCreation->DesiredItemId.ToString());

			//create a new item
			UItemBase* ItemToAdd = NewObject<UItemBase>(this, UItemBase::StaticClass());

			//set the item properties
			ItemToAdd->ID = ItemDataRow->ID;
			ItemToAdd->ItemType = ItemDataRow->ItemType;
			ItemToAdd->ItemQuality = ItemDataRow->ItemQuality;
			ItemToAdd->ItemNumericaData = ItemDataRow->ItemNumericaData;
			ItemToAdd->ItemTextData = ItemDataRow->ItemTextData;
			ItemToAdd->ItemAssetData = ItemDataRow->ItemAssetData;
			ItemToAdd->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
			ItemToAdd->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

			//set the desired quantity based off the passed in data.
			ItemDataForCreation->DesiredQuantiy <= 0 ? ItemToAdd->SetQuantity(1) : ItemToAdd->SetQuantity(ItemDataForCreation->DesiredQuantiy);

			return ItemToAdd;
		}
		break;
	case EItemType::Weapon:
		if (ItemWeaponDataTable && !ItemDataForCreation->DesiredItemId.IsNone())
		{
			//get the item info from the data table.
			const FItemData* ItemDataRow = ItemWeaponDataTable->FindRow<FItemData>(ItemDataForCreation->DesiredItemId, ItemDataForCreation->DesiredItemId.ToString());

			//create a new item
			UItemBase* ItemToAdd = NewObject<UItemBase>(this, UItemBase::StaticClass());

			if (ItemDataRow)
			{
				//set the item properties
				ItemToAdd->ID = ItemDataRow->ID;
				ItemToAdd->ItemType = ItemDataRow->ItemType;
				ItemToAdd->ItemQuality = ItemDataRow->ItemQuality;
				ItemToAdd->ItemNumericaData = ItemDataRow->ItemNumericaData;
				ItemToAdd->ItemTextData = ItemDataRow->ItemTextData;
				ItemToAdd->ItemAssetData = ItemDataRow->ItemAssetData;
				ItemToAdd->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
				ItemToAdd->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

				//set the desired quantity based off the passed in data.
				ItemDataForCreation->DesiredQuantiy <= 0 ? ItemToAdd->SetQuantity(1) : ItemToAdd->SetQuantity(ItemDataForCreation->DesiredQuantiy);
			}

			return ItemToAdd;
		}

		break;
	case EItemType::Netherband:

		//check to see if the data table is set and the desired item is name is set
		if (ItemNetherbandDataTable && !ItemDataForCreation->DesiredItemId.IsNone())
		{
			//get the item info from the data table.
			const FItemData* ItemDataRow = ItemNetherbandDataTable->FindRow<FItemData>(ItemDataForCreation->DesiredItemId, ItemDataForCreation->DesiredItemId.ToString());

			//create a new item
			UItemBase* ItemToAdd = NewObject<UItemBase>(this, UItemBase::StaticClass());

			//set the item properties
			ItemToAdd->ID = ItemDataRow->ID;
			ItemToAdd->ItemType = ItemDataRow->ItemType;
			ItemToAdd->ItemQuality = ItemDataRow->ItemQuality;
			ItemToAdd->ItemNumericaData = ItemDataRow->ItemNumericaData;
			ItemToAdd->ItemTextData = ItemDataRow->ItemTextData;
			ItemToAdd->ItemAssetData = ItemDataRow->ItemAssetData;
			ItemToAdd->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
			ItemToAdd->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

			//set the desired quantity based off the passed in data.
			ItemDataForCreation->DesiredQuantiy <= 0 ? ItemToAdd->SetQuantity(1) : ItemToAdd->SetQuantity(ItemDataForCreation->DesiredQuantiy);

			return ItemToAdd;
		}

		break;
	case EItemType::Consumable:
		//check to see if the data table is set and the desired item is name is set
		if (ItemConsumableDataTable && !ItemDataForCreation->DesiredItemId.IsNone())
		{
			//get the item info from the data table.
			const FItemData* ItemDataRow = ItemConsumableDataTable->FindRow<FItemData>(ItemDataForCreation->DesiredItemId, ItemDataForCreation->DesiredItemId.ToString());

			//create a new item
			UItemBase* ItemToAdd = NewObject<UItemBase>(this, UItemBase::StaticClass());

			//set the item properties
			ItemToAdd->ID = ItemDataRow->ID;
			ItemToAdd->ItemType = ItemDataRow->ItemType;
			ItemToAdd->ItemQuality = ItemDataRow->ItemQuality;
			ItemToAdd->ItemNumericaData = ItemDataRow->ItemNumericaData;
			ItemToAdd->ItemTextData = ItemDataRow->ItemTextData;
			ItemToAdd->ItemAssetData = ItemDataRow->ItemAssetData;
			ItemToAdd->ItemCharacerStatistics = ItemDataRow->ItemCharacerStatistics;
			ItemToAdd->ItemWeaponStatistics = ItemDataRow->ItemWeaponStatistics;

			//set the desired quantity based off the passed in data.
			ItemDataForCreation->DesiredQuantiy <= 0 ? ItemToAdd->SetQuantity(1) : ItemToAdd->SetQuantity(ItemDataForCreation->DesiredQuantiy);

			return ItemToAdd;
		}
		break;
	case EItemType::Quest:
		break;

	default:
		break;
	}
	
	return nullptr;
}

void AChest::SetDataTables()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableMundane(TEXT("/Script/Engine.DataTable'/Game/ThirdPerson/Items/ItemData/DT_MundaneItems.DT_MundaneItems'"));
	if (DataTableMundane.Succeeded())
	{
		ItemMundaneDataTable = DataTableMundane.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableConsumable(TEXT("/Script/Engine.DataTable'/Game/ThirdPerson/Items/ItemData/DT_ConsumableItems.DT_ConsumableItems'"));
	if (DataTableConsumable.Succeeded())
	{
		ItemConsumableDataTable = DataTableConsumable.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableWeapon(TEXT("/Script/Engine.DataTable'/Game/ThirdPerson/Items/ItemData/DT_Weapons.DT_Weapons'"));
	if (DataTableWeapon.Succeeded())
	{
		ItemWeaponDataTable = DataTableWeapon.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableArmor(TEXT("/Script/Engine.DataTable'/Game/ThirdPerson/Items/ItemData/DT_Armor.DT_Armor'"));
	if (DataTableArmor.Succeeded())
	{
		ItemArmorDataTable = DataTableArmor.Object;
	}
	static ConstructorHelpers::FObjectFinder<UDataTable> DataTableQuest(TEXT("/Script/Engine.DataTable'/Game/ThirdPerson/Items/ItemData/DT_QuestItems.DT_QuestItems'"));
	if (DataTableQuest.Succeeded())
	{
		ItemQuestDataTable = DataTableQuest.Object;
	}
}

void AChest::StopChestAudio()
{
	if (AudioComponent)
	{
		AudioComponent->Stop();
	}
}

void AChest::PlayChestAmbientAudio(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsChestLootable)
	{
		if (AudioComponent)
		{
			float FadeInDuration = 5.0f; // Duration in seconds
			float FadeVolumeLevel = 1.0f; // Full volume
			float StartTime = 0.0f; // Start immediately

			AudioComponent->FadeIn(FadeInDuration, FadeVolumeLevel, StartTime);
		}
	}
}

void AChest::StopChestAmbientAudio(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (bIsChestLootable)
	{
		if (AudioComponent)
		{
			float FadeoutDuration = 5.0f; // Duration in seconds
			float FadeVolumeLevel = 0.f; // Full volume
			AudioComponent->FadeOut(FadeoutDuration, FadeVolumeLevel, EAudioFaderCurve::Linear);
		}
	}
}



