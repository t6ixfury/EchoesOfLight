// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "ItemDragDropOperation.generated.h"

class UItemBase;
class UAC_Inventory;
class UW_EquipmentSlot;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UItemDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
public:

	UPROPERTY()
		UItemBase* SourceItem;

	UPROPERTY()
		UAC_Inventory* SourceInventory;

	UPROPERTY()
		UW_EquipmentSlot* EquipmentSlotReference;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:


};
