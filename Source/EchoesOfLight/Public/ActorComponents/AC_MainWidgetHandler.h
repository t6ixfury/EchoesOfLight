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

	UPROPERTY(BlueprintReadWrite)
		UW_MainGUI* GUI;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character")
		TSubclassOf<AMainCharacter> CharacterClass ;

	UPROPERTY(BlueprintReadOnly)
		AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* MainCharacterController;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UW_EquipmentMenu> EquipmentMenuWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Widgets")
		TSubclassOf<UW_Interact> InteractionWidgetClass;

	UPROPERTY()
		UW_EquipmentMenu* EquipmentMenuWidget;

	UPROPERTY()
		UW_Interact* InteractionWidget;

	UPROPERTY()
		bool bIsMenuVisible;

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

	void ShowInteractionWidget() const;
	void HideInteractionWidget() const;
	void UpdateInteractionWidget(const FInteractableData* InteractData) const;


	
		


protected:
	// Called when the game starts
	virtual void BeginPlay() override;



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void InitializePlayer();

	UFUNCTION(BlueprintCallable)
		void CreateAllWidget();

	UFUNCTION(BlueprintCallable)
		void TogglePause();

		
};
