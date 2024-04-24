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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTransform sPlayerTransform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator sPlayerRotation;

	FCharacterStats sStatsLevels;

	FItemWeaponStatistics  sCurrentWeapnStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float sHealth;

	FName CurrentDungeonLevel;

	FName CurrentTownVariation;

};