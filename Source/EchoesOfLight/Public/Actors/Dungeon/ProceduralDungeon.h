// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Grid.h"
#include "ProceduralDungeon.generated.h"

typedef int32 Coordinate;

class ADungeonGridCell;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AProceduralDungeon : public AGrid
{
	GENERATED_BODY()



//FOR VARIABLS
public:

	//Array containing the types of hallways to be placed and is set in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		TArray<TSubclassOf<ADungeonGridCell>> Hallways;

	//Array containing the types of MainRooms to be placed and is set in blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		TArray<TSubclassOf<ADungeonGridCell>> MainRooms;

	//Set the size of the grid like so (GridCellSize X GridCellSize)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Cell Properties")
		int32 GridCellSize;

	//this array gets the name of the Main rooms in the order they are in and will be set in blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Cell Properties")
		TArray<FName> MainRooms_ClassName;






//FOR FUNCTIONS
public:


	AProceduralDungeon();
	
	UFUNCTION()
	bool PlaceMainRoom();

	UFUNCTION()
	void SpawnRoomDungeonCell(FGridCellAttributes GridCellToInitialize);

	UFUNCTION()
	void InitializeDungeonCell(FGridCellAttributes GridCell);



//FOR STRUCTS
public:

	struct DoorCoordinates
	{
		Coordinate x = 0;

		Coordinate y = 0;

		Coordinate z = 0;

	};

};
