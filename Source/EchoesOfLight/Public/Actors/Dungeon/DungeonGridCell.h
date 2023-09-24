// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/GridCell.h"
#include "DungeonGridCell.generated.h"

/**
 * 
 */

UCLASS(Blueprintable, BlueprintType)
class ECHOESOFLIGHT_API ADungeonGridCell : public AGridCell
{
	GENERATED_BODY()

public:

	ADungeonGridCell();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		float ProbabilityToBeSpawn;
	
};
