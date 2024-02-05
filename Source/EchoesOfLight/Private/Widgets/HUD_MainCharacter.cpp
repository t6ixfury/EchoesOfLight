// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/HUD_MainCharacter.h"
#include "Widgets/W_EquipmentMenu.h"
#include "Widgets/W_Interact.h"
#include "Interfaces/Interface_Interaction.h"

AHUD_MainCharacter::AHUD_MainCharacter()
{
}

void AHUD_MainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Creates the main menu widget 
	if (MainMenuWidgetClass)
	{
		MainMenuWidget = CreateWidget<UW_EquipmentMenu>(GetWorld(), MainMenuWidgetClass);
		MainMenuWidget->AddToViewport(5);
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
	//Creates the Interaction Widget
	if (InteractionWidgetClass)
	{
		InteractionWidget = CreateWidget<UW_Interact>(GetWorld(), InteractionWidgetClass);
		InteractionWidget->AddToViewport(-1);
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHUD_MainCharacter::DisplayMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Visible);
		bIsMenuVisible = true;
	}
}

void AHUD_MainCharacter::HideMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		bIsMenuVisible = false;
	}
}

void AHUD_MainCharacter::ToggleMenu()
{
	if (bIsMenuVisible)
	{
		HideMenu();
		//set input mode to game only.
		const FInputModeGameOnly InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		// remove cursor from the screen.
		GetOwningPlayerController()->SetShowMouseCursor(false);
	}
	else
	{
		DisplayMenu();
		//set input mode to game only.
		const FInputModeGameAndUI InputMode;
		GetOwningPlayerController()->SetInputMode(InputMode);
		// remove cursor from the screen.
		GetOwningPlayerController()->SetShowMouseCursor(true);
	}
}

void AHUD_MainCharacter::ShowInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void AHUD_MainCharacter::HideInteractionWidget() const
{
	if (InteractionWidget)
	{
		InteractionWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

void AHUD_MainCharacter::UpdateInteractionWidget(const FInteractableData* InteractData) const
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
