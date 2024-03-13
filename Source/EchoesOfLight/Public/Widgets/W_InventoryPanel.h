// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_InventoryPanel.generated.h"


class UWrapBox;
class UTextBlock;
class AMainCharacter;
class UAC_Inventory;
class UW_InventorySlot;
enum class EItemType :uint8;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_InventoryPanel : public UUserWidget
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
	
public:
	UPROPERTY(meta = (BindWidget))
		UWrapBox* InventoryPanel;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* WeightInfo;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CapacityInfo;

	UPROPERTY()
		AMainCharacter* PlayerCharacter;

	UPROPERTY()
		UAC_Inventory* InventoryReference;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<UW_InventorySlot> InventorySlotClass;
protected:


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:
	//Called to Refresh the Inventory UI.
	void RefreshInventory();


protected:

	void SetInfoText() const;

	virtual void NativeOnInitialized() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	//Handles Equipment being added from slot to Inventory.
	void WasEquipmentAddedToInventory(EItemType EquipmentType);

};
