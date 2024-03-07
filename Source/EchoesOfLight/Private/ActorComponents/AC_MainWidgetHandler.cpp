// Fill out your copyright notice in the Description page of Project Settings.

#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Components/ActorComponent.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_Interact.h"
#include "W_MainGUI.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Structures/Structs.h"
#include "Libraries/BFL_Utility.h"
#include "W_MainGUI.h"
#include "ActorComponents/AC_Inventory.h"
#include "Widgets/W_EquipmentMenu.h"
#include "Interfaces/Interface_Interaction.h"




// Sets default values for this component's properties
UAC_MainWidgetHandler::UAC_MainWidgetHandler()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UAC_MainWidgetHandler::CreateAllPlayerWidgets()
{
	InitializePlayer();
	CreateAllWidget();
}

void UAC_MainWidgetHandler::DisplayMenu()
{
	if (EquipmentMenuWidget)
	{
		EquipmentMenuWidget->SetVisibility(ESlateVisibility::Visible);
		bIsMenuVisible = true;
	}
}

void UAC_MainWidgetHandler::ToggleEquipmentMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();

		//unpause the game.
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		//set input mode to game only.
		const FInputModeGameOnly InputMode;
		MainCharacterController->SetInputMode(InputMode);

		// remove cursor from the screen.
		MainCharacterController->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();

		//set input mode to UI only.
		const FInputModeUIOnly InputMode;
		MainCharacterController->SetInputMode(InputMode);

		//pause the game.
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// remove cursor from the screen.
		MainCharacterController->SetShowMouseCursor(true);
	}
}

void UAC_MainWidgetHandler::HideMenu()
{
	if (EquipmentMenuWidgetClass)
	{
		EquipmentMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsMenuVisible = false;
	}
}

// Called when the game starts
void UAC_MainWidgetHandler::BeginPlay()
{
	Super::BeginPlay();
	CreateAllPlayerWidgets();
}

void UAC_MainWidgetHandler::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UAC_MainWidgetHandler::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void UAC_MainWidgetHandler::UpdateInteractionWidget(const FInteractableData* InteractData) const
{
	if (InteractionWidget)
	{
		if (InteractionWidget->GetVisibility() == ESlateVisibility::Collapsed)
		{
			InteractionWidget->SetVisibility(ESlateVisibility::Visible);
		}

		InteractionWidget->UpdateWidget(InteractData);
	}
}


// Called every frame
void UAC_MainWidgetHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UAC_MainWidgetHandler::InitializePlayer()
{

	MainCharacter = Cast<AMainCharacter>(GetOwner());
	UE_LOG(LogTemp, Warning, TEXT("Maincharacter set"))
	if (MainCharacter)
	{
		MainCharacterController = Cast<APlayerController>(MainCharacter->GetController());
		UE_LOG(LogTemp, Warning, TEXT("MainCharacter present"));
	}
}

void UAC_MainWidgetHandler::CreateAllWidget()
{
	//Creates the player character GUI
	if (MainCharacterController && GUI_Class)
	{
		GUI = CreateWidget<UW_MainGUI>(MainCharacterController, GUI_Class);
		if (GUI)
		{
			GUI->AddToViewport();
		}

	}

	if (EquipmentMenuWidgetClass)
	{
		EquipmentMenuWidget = CreateWidget<UW_EquipmentMenu>(MainCharacterController, EquipmentMenuWidgetClass);
		EquipmentMenuWidget->AddToViewport();
		EquipmentMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Creates the Interaction Widget
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UW_Interact>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}


void UAC_MainWidgetHandler::TogglePause()
{

}

