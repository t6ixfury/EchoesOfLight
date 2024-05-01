// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Structures/Structs.h"
#include "Actors/Items/ItemBase.h"
#include "Save_PlayerInfo.generated.h"

/**
 * 
 */

UCLASS()
class ECHOESOFLIGHT_API USave_PlayerInfo : public USaveGame
{
	GENERATED_BODY()
	
public:

	UPROPERTY()
	FCharacterStats sStatsLevels;

	UPROPERTY()
	FItemWeaponStatistics  sCurrentWeapnStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sHealth = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName sCurrentDungeonLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName sCurrentTownVariation;

};