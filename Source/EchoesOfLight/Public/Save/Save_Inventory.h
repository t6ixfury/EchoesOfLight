// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/Master_SaveGame.h"
#include "Engine/DataTable.h"
#include "Save_Inventory.generated.h"


/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API USave_Inventory : public UMaster_SaveGame
{
	GENERATED_BODY()

public:
	USave_Inventory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		TArray<FDataTableRowHandle> sInventory;

	
};
