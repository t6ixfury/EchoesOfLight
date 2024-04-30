// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Villager.h"
#include "ActorComponents/DialogueSystem.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MainCharacter.h"
#include "Actors/Camera/DialogueCamera.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Widgets/W_DialogueBox.h"
#include "Widgets/W_DialogueGui.h"
#include "EnhancedInputComponent.h" 
#include "Actors/Items/ItemBase.h"
#include "ActorComponents/AC_Inventory.h"



// Sets default values
AVillager::AVillager()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Dialogue = CreateDefaultSubobject<UDialogueSystem>(TEXT("Dialogue System"));

}

void AVillager::BeginFocus()
{
	UE_LOG(LogTemp, Warning, TEXT("BeginFocus Villager"))

	if (Dialogue->DialogueData.InteractionMontage)
	{
		USkeletalMeshComponent* meshcomp = GetMesh();
		
		UAnimInstance* anim = meshcomp->GetAnimInstance();

		anim->Montage_Play(Dialogue->DialogueData.InteractionMontage);
		anim->Montage_JumpToSection("");
	}
}

void AVillager::EndFocus()
{
}

void AVillager::BeginInteract()
{
}

void AVillager::EndInteract()
{
	if (CharacterRef)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController)
		{
			//set camera view to dialoge camera.
			PlayerController->SetViewTargetWithBlend(CharacterRef, .8f);

			UCharacterMovementComponent* MovementComponent = CharacterRef->GetCharacterMovement();
			if (MovementComponent)
			{
				//stops all movement on character.
				MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);

				CharacterRef->MainWidgetHandlerComponent->RemoveDialogueWidget();

				//hides all widgets
				CharacterRef->MainWidgetHandlerComponent->ShowHUD();

				//hides the main character in game
				CharacterRef->SetActorHiddenInGame(false);

				if (CharacterRef->LeftHandWeapon && CharacterRef->RightHandWeapon)
				{
					CharacterRef->LeftHandWeapon->SetActorHiddenInGame(false);
					CharacterRef->RightHandWeapon->SetActorHiddenInGame(false);
				}

				Dialogue->bIsTalking = false;
				CharacterRef->DialogueSystem->bIsTalking = false;
				CharacterRotation = FRotator();
				DialogueCamera = nullptr;
				SetActorRotation(FRotator::ZeroRotator);

				
			}

		}
	}

	if (!ItemName.IsNone())
	{
		switch (Itemtype)
		{
		case EItemType::Amulet:

			if (ItemAmuletDataTable)
			{
				//get the item info from the data table.
				const FItemData* ItemDataRow = ItemAmuletDataTable->FindRow<FItemData>(ItemName, ItemName.ToString());

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
				ItemToAdd->ItemStatistics = ItemDataRow->ItemStatistics;

				//set the desired quantity based off the passed in data.
				ItemToAdd->SetQuantity(ItemQuantity);

				CharacterRef->PlayerInventory->HandleAddItem(ItemToAdd);
			}
			break;
		case EItemType::Weapon:

			if (ItemWeaponDataTable)
			{
				//get the item info from the data table.
				const FItemData* ItemDataRow = ItemWeaponDataTable->FindRow<FItemData>(ItemName, ItemName.ToString());

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
				ItemToAdd->ItemStatistics = ItemDataRow->ItemStatistics;

				//set the desired quantity based off the passed in data.
				ItemToAdd->SetQuantity(ItemQuantity);

				CharacterRef->PlayerInventory->HandleAddItem(ItemToAdd);
			}

			break;
		case EItemType::Netherband:

			if (ItemNetherbandDataTable)
			{
				//get the item info from the data table.
				const FItemData* ItemDataRow = ItemNetherbandDataTable->FindRow<FItemData>(ItemName, ItemName.ToString());

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
				ItemToAdd->ItemStatistics = ItemDataRow->ItemStatistics;

				//set the desired quantity based off the passed in data.
				ItemToAdd->SetQuantity(ItemQuantity);

				CharacterRef->PlayerInventory->HandleAddItem(ItemToAdd);
			}

			break;
		case EItemType::Consumable:

			if (ItemConsumbableDataTable)
			{
				//get the item info from the data table.
				const FItemData* ItemDataRow = ItemConsumbableDataTable->FindRow<FItemData>(ItemName, ItemName.ToString());

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
				ItemToAdd->ItemStatistics = ItemDataRow->ItemStatistics;

				//set the desired quantity based off the passed in data.
				ItemToAdd->SetQuantity(ItemQuantity);

				CharacterRef->PlayerInventory->HandleAddItem(ItemToAdd);
			}
			break;
		
		 default:
			break;
		}

		CharacterRef->SaveAll();
	}

}

void AVillager::Interact(AMainCharacter* PlayerCharacter)
{

	if (PlayerCharacter && !Dialogue->bIsTalking)
	{
		CharacterRef = PlayerCharacter;
		Dialogue->bIsTalking = true;
		PlayerCharacter->DialogueSystem->bIsTalking = true;

		//Set character camera to villager location. and lock position
		SetDialogueCameraView(PlayerCharacter);

		// Display character dialogue widget with village text
		PlayerCharacter->MainWidgetHandlerComponent->CreateDialogueWidget();
		Dialogue->RetrieveDialogueData();

		if (PlayerCharacter->MainWidgetHandlerComponent->DialogueGui)
		{
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->SetFocus();
			Dialogue->SetDialogueSentencesArray(Dialogue->DialogueData.Dialoguetext);
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->DialogueBox->SetName(Dialogue->DialogueData.Name);
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->DialogueBox->SetDialogueText(Dialogue->DialogueSentences[0]);
			PlayerCharacter->MainWidgetHandlerComponent->DialogueGui->DialogueBox->sentences = Dialogue->DialogueSentences;
		}

	}

}

void AVillager::SetInteractableData()
{
	InteractableData.Action = FText::FromString("Talk");
	InteractableData.InteractableType = EInteractableType::Villager;
	InteractableData.InteractionDuration = 0;
	InteractableData.Quantity = 0;
}

void AVillager::SetVillagerRotation(float DeltaTime)
{
	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), CharacterRotation, DeltaTime, RotationSpeed);
	SetActorRotation(NewRotation);


}

void AVillager::SetDialogueCameraView(AMainCharacter* Character)
{
	if (Dialogue->bIsTalking)
	{
		FVector VillagerToCharacter = Character->GetActorLocation() - GetActorLocation();
		VillagerToCharacter.Normalize();



		// Get the villager's forward vector
		FVector VillagerForward = Character->GetActorForwardVector();

		// Calculate the dot product
		float DotProduct = FVector::DotProduct(VillagerForward, VillagerToCharacter);

		FVector CameraLocation;
		if (DotProduct > 0) {
			CameraLocation = GetActorLocation() + VillagerForward * 200;
		}
		else {
			CameraLocation = GetActorLocation() - VillagerForward * 200;
		}

		// Ensure the camera always faces towards the villager
		FRotator CameraRotation = FRotationMatrix::MakeFromX(GetActorLocation() - CameraLocation).Rotator() *1;

		CharacterRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), CameraLocation);

		DialogueCamera = GetWorld()->SpawnActor<ADialogueCamera>(ADialogueCamera::StaticClass(), CameraLocation, CameraRotation);

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		if (PlayerController && DialogueCamera)
		{
			//set camera view to dialoge camera.
			PlayerController->SetViewTargetWithBlend(DialogueCamera, .8f);

			UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
			if (MovementComponent)
			{
				//stops all movement on character.
				MovementComponent->SetMovementMode(EMovementMode::MOVE_None);

				//hides all widgets
				Character->MainWidgetHandlerComponent->HideHUD();
				Character->MainWidgetHandlerComponent->HideInteractionWidget();

				//hides the main character in game
				Character->SetActorHiddenInGame(true);
				if (Character->LeftHandWeapon && Character->RightHandWeapon)
				{
					Character->LeftHandWeapon->SetActorHiddenInGame(true);
					Character->RightHandWeapon->SetActorHiddenInGame(true);
				}
			}

		}
	}
	
}

// Called when the game starts or when spawned
void AVillager::BeginPlay()
{
	Super::BeginPlay();
	SetInteractableData();

	
}

// Called every frame
void AVillager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Dialogue->bIsTalking && CharacterRef->MainWidgetHandlerComponent->DialogueGui->DialogueBox->bHasDialogueText)
	{
		SetVillagerRotation(DeltaTime);
	}
	if (CharacterRef)
	{
		if (CharacterRef->MainWidgetHandlerComponent->DialogueGui)
		{
			if (!CharacterRef->MainWidgetHandlerComponent->DialogueGui->DialogueBox->bHasDialogueText)
			{
				EndInteract();
			}
		}
	}

}

// Called to bind functionality to input
void AVillager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

