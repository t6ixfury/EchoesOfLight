// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUD_MainCharacter.generated.h"


class UW_MainMenu;
class UW_Interact;
struct FInteractableData;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AHUD_MainCharacter : public AHUD
{
	GENERATED_BODY()

public:
	//---------------------------------------------------------------------------------------------------------------------------
	//	PROPERTIES AND VARIABLES
	//---------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UW_MainMenu> MainMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UW_Interact> InteractionWidgetClass;

	UPROPERTY()
	bool bIsMenuVisible;

	//---------------------------------------------------------------------------------------------------------------------------
	//	FUNCTIONS
	//---------------------------------------------------------------------------------------------------------------------------

	AHUD_MainCharacter();
	
	void DisplayMenu();
	void HideMenu();
	void ToggleMenu();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget( const FInteractableData* InteractData) const;


protected:
	//---------------------------------------------------------------------------------------------------------------------------
	//	PROPERTIES AND VARIABLES
	//---------------------------------------------------------------------------------------------------------------------------
	UPROPERTY()
		UW_MainMenu* MainMenuWidget;
		UPROPERTY()
		UW_Interact* InteractionWidget;


	//---------------------------------------------------------------------------------------------------------------------------
	//	FUNCTIONS
	//---------------------------------------------------------------------------------------------------------------------------
	virtual void BeginPlay() override;
	
};
