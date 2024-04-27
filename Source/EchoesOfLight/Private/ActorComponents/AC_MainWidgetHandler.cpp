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
#include "Widgets/HUD_MainCharacter.h"
#include "Widgets/W_DialogueGui.h"
#include "Widgets/W_DialogueBox.h"
#include "Widgets/W_Alert.h"
#include "TimerManager.h"
#include "Sound/SoundBase.h"
#include "Widgets/W_PauseMenu.h"
#include "Components/WidgetComponent.h"





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

void UAC_MainWidgetHandler::CreateDialogueWidget()
{
	if (MainCharacterController && DialogueGUI_Class)
	{
		DialogueGui = CreateWidget<UW_DialogueGui>(MainCharacterController, DialogueGUI_Class);
		if (DialogueGui)
		{
			DialogueGui->AddToViewport();
			FInputModeGameOnly InputMode;
			MainCharacterController->SetInputMode(InputMode);
			MainCharacterController->SetShowMouseCursor(false);
		}

	}

}

void UAC_MainWidgetHandler::RemoveDialogueWidget()
{
	if (DialogueGui && MainCharacterController)
	{
		DialogueGui->RemoveFromParent();
		//set input mode to game only.
		const FInputModeGameOnly InputMode;
		MainCharacterController->SetInputMode(InputMode);
		DialogueGui = nullptr;

	}
}

void UAC_MainWidgetHandler::ShowAlertWidget(FText message)
{
	UWorld* World = GetWorld();
	if (AlertWidgetClass && MainCharacterController && World)
	{
		UW_Alert* Widget = CreateWidget<UW_Alert>(MainCharacterController, ExperienceAlertWidgetClass);
		if (Widget)
		{
			AlertWidget = Widget;
			AlertWidget->SetAlertMessageText(message);
			AlertWidget->AddToPlayerScreen();
			float time = AlertWidget->PlayAlertAnimation();

			World->GetTimerManager().SetTimer(AlertTimer, this, &UAC_MainWidgetHandler::RemoveAlertWidget, time);
		}

	}
}

void UAC_MainWidgetHandler::ShowExperienceAlertWidget(FText message)
{
	UWorld* World = GetWorld();
	if (MainCharacterController && World)
	{
		// Check if an alert widget already exists, and if so, remove it immediately.
		if (AlertWidget)
		{
			AlertWidget->RemoveFromParent();
			AlertWidget->MarkAsGarbage();
			AlertWidget = nullptr;
			World->GetTimerManager().ClearTimer(AlertTimer);
		}

		// Create a new widget.
		UW_Alert* Widget = CreateWidget<UW_Alert>(MainCharacterController, ExperienceAlertWidgetClass);
		if (Widget)
		{
			AlertWidget = Widget;
			AlertWidget->SetAlertMessageText(message);
			AlertWidget->AddToPlayerScreen();

			float time = AlertWidget->PlayAlertAnimation();

			// Set a timer to remove the widget after the animation.
			World->GetTimerManager().SetTimer(AlertTimer, this, &UAC_MainWidgetHandler::RemoveAlertWidget, time);
		}
	}
}

void UAC_MainWidgetHandler::ShowAlertWidget(FText message, FText Title)
{
	UWorld* World = GetWorld();
	if (AlertWidgetClass && MainCharacterController && World)
	{
		UW_Alert* Widget = CreateWidget<UW_Alert>(MainCharacterController, ExperienceAlertWidgetClass);
		if (Widget)
		{
			AlertWidget = Widget;
			AlertWidget->SetAlertMessageText(message);
			AlertWidget->SetAlertTitleText(Title);
			AlertWidget->AddToPlayerScreen();
			float time = AlertWidget->PlayAlertAnimation();

			World->GetTimerManager().SetTimer(AlertTimer, this, &UAC_MainWidgetHandler::RemoveAlertWidget, time);
		}

	}
}

void UAC_MainWidgetHandler::ShowLevelAlertWidget(FText message)
{
	UWorld* World = GetWorld();
	if (LevelAlertWidgetClass && MainCharacterController && World)
	{
		if (LevelWidget)
		{
			LevelWidget->RemoveFromParent();
			LevelWidget->MarkAsGarbage();
			LevelWidget = nullptr;
			World->GetTimerManager().ClearTimer(LevelAlertTimer);
		}

		UW_Alert* Widget = CreateWidget<UW_Alert>(MainCharacterController, LevelAlertWidgetClass);
		if (Widget)
		{
			LevelWidget = Widget;
			LevelWidget->SetAlertMessageText(message);
			LevelWidget->AddToPlayerScreen();
			float time = LevelWidget->PlayAlertAnimation();

			World->GetTimerManager().SetTimer(LevelAlertTimer, this, &UAC_MainWidgetHandler::RemoveLevelAlertWidget, time);
		}

	}
}

void UAC_MainWidgetHandler::RemoveAlertWidget()
{
	if (AlertWidget)
	{
		AlertWidget->RemoveFromParent();
		AlertWidget->MarkAsGarbage();
		AlertWidget = nullptr;
		
		GetWorld()->GetTimerManager().ClearTimer(LevelAlertTimer);
	}
}

void UAC_MainWidgetHandler::RemoveLevelAlertWidget()
{
	if (LevelWidget)
	{
		LevelWidget->RemoveFromParent();
		LevelWidget->MarkAsGarbage();
		LevelWidget = nullptr;

		GetWorld()->GetTimerManager().ClearTimer(AlertTimer);
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
		const FInputModeGameAndUI InputMode;
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

void UAC_MainWidgetHandler::OpenPauseMenu()
{
	PauseMenuWidget = CreateWidget<UW_PauseMenu>(MainCharacterController, PauseMenuWidgetClass);

	if (PauseMenuWidget)
	{
		PauseMenuWidget->AddToViewport(10);
		PauseMenuWidget->SetVisibility(ESlateVisibility::Visible);
		MainCharacterController->SetPause(true);

		FInputModeUIOnly UI;
		MainCharacterController->bShowMouseCursor = true;
		MainCharacterController->SetInputMode(UI);

		if (PauseMenuSound)
		{
			UGameplayStatics::PlaySound2D(this, PauseMenuSound);
		}
	}
}

void UAC_MainWidgetHandler::ClosePauseMenu()
{
	if (PauseMenuWidget)
	{
		PauseMenuWidget->RemoveFromParent();
		PauseMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		MainCharacterController->SetPause(false);

		FInputModeGameOnly Game;
		MainCharacterController->bShowMouseCursor = false;
		MainCharacterController->SetInputMode(Game);

		PauseMenuWidget->MarkAsGarbage();
		PauseMenuWidget = nullptr;
	}
}

void UAC_MainWidgetHandler::TogglePauseMenu()
{
	if (IsValid(PauseMenuWidget))
	{
		ClosePauseMenu();
	}
	else
	{
		OpenPauseMenu();
	}
}


void UAC_MainWidgetHandler::HideHUD()
{	
	if (GUI)
	{
		GUI->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UAC_MainWidgetHandler::ShowHUD()
{
	if (GUI)
	{
		GUI->SetVisibility(ESlateVisibility::Visible);
	}
}

