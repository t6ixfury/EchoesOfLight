// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TimerManager.h"
#include "Engine/DataTable.h"

#include "AC_MainWidgetHandler.generated.h"

class UW_Interact;
class UW_MainGUI;
class AMainCharacter;
class UBFL_Utility;
class UW_EquipmentMenu;
struct FInteractableData;
class AHUD_MainCharacter;
class UW_DialogueGui;
class UW_Alert;
struct FTimerHandle;
class UW_PauseMenu;
class USoundBase;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UAC_MainWidgetHandler : public UActorComponent
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:	
	// Sets default values for this component's properties
	UAC_MainWidgetHandler();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_MainGUI> GUI_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_DialogueGui> DialogueGUI_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_Alert> AlertWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_Alert> LevelAlertWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_Alert> ExperienceAlertWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TSubclassOf<AMainCharacter> CharacterClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_EquipmentMenu> EquipmentMenuWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_Interact> InteractionWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget classes")
		TSubclassOf<UW_PauseMenu> PauseMenuWidgetClass;



	//used for spawning the experience alert
	UPROPERTY()
	class UWidgetComponent* WidgetComp;

	UPROPERTY(BlueprintReadOnly)
		AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* MainCharacterController;

	UPROPERTY()
		UW_EquipmentMenu* EquipmentMenuWidget;

	UPROPERTY()
		UW_Interact* InteractionWidget;

	UPROPERTY()
		UW_PauseMenu* PauseMenuWidget;

	UPROPERTY()
		UW_DialogueGui* DialogueGui;

	UPROPERTY()
		UW_MainGUI* GUI;
	UPROPERTY()
		UW_Alert* AlertWidget;

	UPROPERTY()
		UW_Alert* LevelWidget;


//-----------------------------SOUNDS--------------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI Sounds")
		USoundBase* PauseMenuSound;


	UPROPERTY()
		bool bIsMenuVisible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget's properties")
		float AlertDuration = 5;

	//Timers

	FTimerHandle AlertTimer;

	FTimerHandle LevelAlertTimer;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

	UFUNCTION()
		void CreateAllPlayerWidgets();

	UFUNCTION()
		void ToggleEquipmentMenu();

	UFUNCTION()
		void HideMenu();

	UFUNCTION()
		void DisplayMenu();

	UFUNCTION()
		void CreateDialogueWidget();

	UFUNCTION()
		void RemoveDialogueWidget();

	void ShowAlertWidget(FText message);

	UFUNCTION(Blueprintcallable)
	void ShowExperienceAlertWidget(FText message);
	void ShowAlertWidget(FText message, FText Title);

	void ShowLevelAlertWidget(FText message);

	void RemoveAlertWidget();

	void RemoveLevelAlertWidget();

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractData) const;

	void InitializePlayer();

	void CreateAllWidget();

	void OpenPauseMenu();
	void ClosePauseMenu();

	void TogglePauseMenu();

	void HideHUD();

	void ShowHUD();



	
		


protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


		
};
