// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Grid.h"
#include "ProceduralDungeon.generated.h"

typedef int32 Coordinate;

class ADungeonGridCell;

class AGrid;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class ECHOESOFLIGHT_API AProceduralDungeon : public AActor
{
	GENERATED_BODY()



//FOR VARIABLS
public:

	//Array containing the types of hallways to be placed and is set in blueprints
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		TArray<TSubclassOf<ADungeonGridCell>> Hallways;

	//Array containing the types of MainRooms to be placed and is set in blueprints
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		TArray<TSubclassOf<ADungeonGridCell>> MainRooms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Dungeon Cell Properties")
		TArray<ADungeonGridCell*> roomOnGrid;

	//Set the size of the grid like so (GridCellSize X GridCellSize)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Cell Properties")
		float GridCellSize;

	//this array gets the name of the Main rooms in the order they are in and will be set in blueprints.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Cell Properties")
		TArray<FName> MainRooms_ClassName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Cell Properties")
		int32 RoomSpacing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		AGrid* DungeonGrid;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		float gridSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid")
		int32 numberOfRoomsToSpawn;







//FOR FUNCTIONS
public:


	AProceduralDungeon();

	virtual void BeginPlay() override;

	void TestGridValues();

	void DrawOccupiedCells();


	UFUNCTION()
		void SetMainRoomsAndHallways();
	
	UFUNCTION()
		TSubclassOf<ADungeonGridCell> MainRoomToSpawn();

	UFUNCTION()
		void PlaceRoomsOnGrid();

	UFUNCTION()
		void SpawnRoom(TSubclassOf<ADungeonGridCell> roomToSpawn, FGridCellAttributes currentCell);

	UFUNCTION()
		int32 GridCellToSpawnOn(TSubclassOf<ADungeonGridCell> roomToSpawn);

	UFUNCTION()
		bool CanRoomFitAtGridCell(TSubclassOf<ADungeonGridCell> roomToSpawn, int32 index);

	UFUNCTION()
		void MarkCellsAsUsed(TSubclassOf<ADungeonGridCell> roomToSpawn, int32 index);

};
