// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/Master_SaveGame.h"
#include "Engine/DataTable.h"
#include "Save_Inventory.generated.h"

class UItemBase;
/**
 * 
 */

struct FItemSaveInfo;

UCLASS()
class ECHOESOFLIGHT_API USave_Inventory : public UMaster_SaveGame
{
	GENERATED_BODY()

public:
	USave_Inventory();

	//Represents the total weight the player is currently carring.
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		float sInventoryTotalWeight = 0;

	// Represents the total number of slots in the inventory.
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
		int32 sInventorySlotsCapacity= 25;

	//Represents the total Weight a player can carry.
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
		float sInventoryWeightCapacity = 50;

	//An array of all the items in the inventory.
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
		TArray<FItemSaveInfo> sInventoryContents;

	
};
