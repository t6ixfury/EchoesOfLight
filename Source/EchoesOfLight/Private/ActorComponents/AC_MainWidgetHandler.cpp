// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/ActorComponent.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Character/MainCharacter.h"
#include "Widgets/W_Interact.h"
#include "W_MainGUI.h"
#include "Widgets/W_PauseMenu.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"
#include "Structures/Structs.h"
#include "Libraries/BFL_Utility.h"
#include "Widgets/W_Inventory.h"
#include "W_MainGUI.h"
#include "ActorComponents/AC_Inventory.h"




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
	CreateMainWidget();
	CreateInventoryWidget();
}

// Called when the game starts
void UAC_MainWidgetHandler::BeginPlay()
{
	Super::BeginPlay();
	InitializePlayerWidgetsEvent.AddDynamic(this, &UAC_MainWidgetHandler::CreateAllPlayerWidgets);
	InitializePlayerWidgetsEvent.Broadcast();

	
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
	
	if (MainCharacter)
	{
		MainCharacterController = Cast<APlayerController>(MainCharacter->GetController());
	}
}

void UAC_MainWidgetHandler::CreateMainWidget()
{
	if (MainCharacterController)
	{
		GUI = CreateWidget<UW_MainGUI>(MainCharacterController, UW_MainGUI::StaticClass());
	}
}

void UAC_MainWidgetHandler::CreateInventoryWidget()
{
	if (GUI)
	{
		if (MainCharacter->InventoryComponent->InventoryWidget)
		{
			GUI->Inventory = CreateWidget<UW_Inventory>(MainCharacter->InventoryComponent->InventoryWidget);
		}

	}
}

void UAC_MainWidgetHandler::TogglePause()
{
	if (PauseMenu)
	{
		if (PauseMenu->IsInViewport())
		{
			PauseMenu->RemoveFromParent();
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			if (MainCharacterController)
			{
				MainCharacterController->bPlayerIsWaiting = false;
				MainCharacterController->bShowMouseCursor = false;
			}
			

		}
		else
		{
			PauseMenu->AddToViewport();
			if (Utility->BPL_GetGameSettingsInfo(GameSetting).bStopGameTimeWhenPauseMenu)
			{
				UGameplayStatics::SetGamePaused(GetWorld(), true);
				if (MainCharacterController)
				{
					FInputModeUIOnly InputMode;
					InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock); 
					MainCharacterController->SetInputMode(InputMode);
					MainCharacterController->bShowMouseCursor = true;
				
				}

			}


		}

	}
	
}

