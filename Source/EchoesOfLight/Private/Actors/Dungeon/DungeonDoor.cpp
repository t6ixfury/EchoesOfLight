// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Actors/Dungeon/DungeonDoor.h"
#include "Character/MainCharacter.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "ActorComponents/AC_Inventory.h"
#include "Actors/Items/ItemBase.h"

//engine
#include "Components/StaticMeshComponent.h"


// Sets default values
ADungeonDoor::ADungeonDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LeftDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left Door"));

	RightDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right Door"));

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));

	RootComponent = DoorFrame;

	LeftDoor->SetupAttachment(RootComponent);
	RightDoor->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ADungeonDoor::BeginPlay()
{
	Super::BeginPlay();
	UpdateInteractable();
}

// Called every frame
void ADungeonDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsOperating)
	{
		// Interpolate rotation for both doors
		FRotator NewLeftRotation = FMath::RInterpTo(LeftDoor->GetRelativeRotation(), TargetLeftDoorRotation, DeltaTime, RotationSpeed);
		LeftDoor->SetRelativeRotation(NewLeftRotation);

		FRotator NewRightRotation = FMath::RInterpTo(RightDoor->GetRelativeRotation(), TargetRightDoorRotation, DeltaTime, RotationSpeed);
		RightDoor->SetRelativeRotation(NewRightRotation);

		UE_LOG(LogTemp, Warning, TEXT("Operating"));

		// Check if the door has reached its target rotation
		if (NewLeftRotation.Equals(TargetLeftDoorRotation, 0.01f) && NewRightRotation.Equals(TargetRightDoorRotation, 0.01f))
		{
			bIsOperating = false; // Stop interpolating
			bIsDoorOpen = !bIsDoorOpen; // Update door state
		}
	}

}

void ADungeonDoor::BeginFocus()
{
}

void ADungeonDoor::EndFocus()
{
}

void ADungeonDoor::BeginInteract()
{
}

void ADungeonDoor::EndInteract()
{
}

void ADungeonDoor::Interact(AMainCharacter* PlayerCharacter)
{
	if (HasDungeonKey(PlayerCharacter) && !bIsDoorOpen)
	{
		OperateDoor();
	}
	else
	{
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->MainWidgetHandlerComponent->HideInteractionWidget();
			PlayerCharacter->MainWidgetHandlerComponent->ShowAlertWidget(FText::FromString("You do not have the dungeon key!\nHint: Try killing the rest of the enemies."));
			UE_LOG(LogTemp, Warning, TEXT("Alert"));
		}
	}
}

void ADungeonDoor::OperateDoor()
{
	if (!bIsOperating)
	{
		bIsOperating = true; // Start interpolating

		if (!bIsDoorOpen)
		{
			TargetLeftDoorRotation = FRotator(0, -80, 0);
			TargetRightDoorRotation = FRotator(0, 80, 0);
			UE_LOG(LogTemp, Warning, TEXT("Door Opening"));
		}
		else
		{
			TargetLeftDoorRotation = FRotator(0, 0, 0); // Assume initial rotation is (0,0,0)
			TargetRightDoorRotation = FRotator(0, 0, 0);
			UE_LOG(LogTemp, Warning, TEXT("Door Closing"));
		}
	}

}

void ADungeonDoor::UpdateInteractable()
{
	InteractableData.Action = FText::FromString("Open");
	InteractableData.InteractableType = EInteractableType::Device;
	InteractableData.Name = FText::FromString("Dungeon Door");
}

bool ADungeonDoor::HasDungeonKey(AMainCharacter* PlayerCharacter)
{
	if (IsValid(PlayerCharacter))
	{
		UItemBase* key = PlayerCharacter->PlayerInventory->FindItembyName(DungeonKeyName);

		if (IsValid(key))
		{
			PlayerCharacter->PlayerInventory->RemoveSingleInstanceOfItem(key);
			return true;
		}

	}
	return false;
}

