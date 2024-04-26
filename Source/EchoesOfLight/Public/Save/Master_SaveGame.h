// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Master_SaveGame.generated.h"

/**
 * 
 */

class USave_Experience;
class USave_Inventory;


UCLASS()
class ECHOESOFLIGHT_API UMaster_SaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName sCurrentDungeonLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName sCurrentTownVariation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 sCurrentTownIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 sCurrentDungeonIndex;
	
};
