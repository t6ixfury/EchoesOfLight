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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		E_GridCellWallType Left_WallType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		E_GridCellWallType Right_WallType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		E_GridCellWallType Top_WallType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		E_GridCellWallType Bottom_WallType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		E_RoomType RoomType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		int32 Room_X_Dimensions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		int32 Room_Y_Dimensions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		bool bDoesTakeMultipleCells;
};
