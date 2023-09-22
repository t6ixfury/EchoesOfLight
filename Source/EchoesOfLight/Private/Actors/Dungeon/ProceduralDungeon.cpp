// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dungeon/ProceduralDungeon.h"
#include "Actors/Dungeon/DungeonGridCell.h"
#include "Math/UnrealMathUtility.h"



//Constructor Function.
AProceduralDungeon::AProceduralDungeon()
{
	NumberOfGridCells = 50;
	GridCellSize = 800;
}

// Randomly Places rooms through dungeon grid.
bool AProceduralDungeon::PlaceMainRoom()
{
	bool bisRoomsPlaced = false;
	// Number to check the random value against so it does not pick the same grid cell twice.
	int8 prevRandomNumber = 0;

	// Creates and Initializes the grid.
	CreateGrid(GridCellSize);

	//Size of the array holding the main rooms
	int8 NumberOfMainRooms = MainRooms.Num();

	// attempts allowed for room placements.
	int8 Attempts = 100;

	//a while loop to place a random rooom on the grid. will continue until all rooms have been placed with an attempt limit of 100.
	while (NumberOfMainRooms > 0 || Attempts > 0)
	{
		//Random value to select a random grid square
		int8 RandomValue = FMath::RandRange(0, (NumberOfGridCells - 1));

		//checks if the same random value has been choosen and if not check if the cell is available to be placed on.
		if ((RandomValue != prevRandomNumber) && (Grid[RandomValue].bIsCellOccupied == false))
		{
			if (MainRooms[NumberOfMainRooms])
			{
			}
			// set the new prev number
			prevRandomNumber = RandomValue;



			//decrements the main rooms after placement
			NumberOfMainRooms -= 1;
		}
		// if placement fail decrement attempts
		else
		{
			Attempts -= 1;
		}
	}
	// set the return variable. true if all rooms were placed false if all rooms were not placed.
	if (NumberOfMainRooms == 0)
	{
		bisRoomsPlaced = true;
	}

	//IMPORTANT NOTE: It may be possible that some rooms place but not all so if this function needs to be re-called we need to delete all the rooms that were placed.
	// Might be better to save all the locations in the while loop and spawn them in the return variable check to stop needless spawning.

	return bisRoomsPlaced;
}

// Spawns the ADungeonCell Actor and passes the reference to the grid of whats occupying the cell.
void AProceduralDungeon::SpawnRoomDungeonCell(FGridCellAttributes GridCellToInitialize)
{
	UWorld* level = GetWorld();

	if (level)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		// spawn needs to be changed to the bp class of the main room.
		ADungeonGridCell* NewDungeonCell = level->SpawnActor<ADungeonGridCell>(ADungeonGridCell::StaticClass(), GridCellToInitialize.CellPositionToSpawnInTheLevel, FRotator(0, 0, 0), SpawnParams);

		GridCellToInitialize.Cell = NewDungeonCell;
	}

}
//This function sets the reference of the edge locations for the grid to the cell.
void AProceduralDungeon::InitializeDungeonCell(FGridCellAttributes GridCell)
{
	if (GridCell.Cell)
	{
		FVector Location = GridCell.CellPositionInWorld;

		GridCell.Cell->CellProperties.Top_EdgeLocation.Start = FVector(Location.X, Location.Y, 0);
		GridCell.Cell->CellProperties.Top_EdgeLocation.End = FVector((Location.X + 1), Location.Y, 0);

		GridCell.Cell->CellProperties.Bottom_EdgeLocation.Start = FVector(Location.X, (Location.Y + GridCellSize), 0);
		GridCell.Cell->CellProperties.Bottom_EdgeLocation.End = FVector((Location.X + 1), (Location.Y +GridCellSize), 0);

		GridCell.Cell->CellProperties.Left_EdgeLocation.Start = FVector(Location.X, Location.Y, 0);
		GridCell.Cell->CellProperties.Left_EdgeLocation.End = FVector(Location.X, (Location.Y + GridCellSize), 0);

		GridCell.Cell->CellProperties.Right_EdgeLocation.Start = FVector((Location.X + 1), Location.Y, 0);
		GridCell.Cell->CellProperties.Right_EdgeLocation.End = FVector((Location.X + 1), (Location.Y + GridCellSize), 0);
	}
}
