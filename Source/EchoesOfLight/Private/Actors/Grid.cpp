// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grid.h"
#include "Actors/GridCell.h"
#include "Engine/StaticMesh.h"
#include "Actors/Dungeon/DungeonGridCell.h"


// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	GridHeight = 0;
	GridWidth = 0;
	GridSize = 0;
	NumberOfGridCells = 0;
	Grid_SpawnAble = Grid;
	//FGridCellAttributes Attributes;
	//Grid.Init(Attributes, (NumberOfGridCells*NumberOfGridCells));

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AGrid::CreateGrid(float cellsize)
{
	Grid.Empty();

	int32 GridCellIndex = 0;

	for (int i = 0; i < NumberOfGridCells; i++)
	{
		for (int j = 0; j < NumberOfGridCells; j++)
		{
			Grid.Add(FGridCellAttributes());
			
			//UE_LOG(LogTemp, Warning, TEXT("Grid is %s"), Grid.IsEmpty() ? TEXT("empty") : TEXT("not empty"));
			//UE_LOG(LogTemp, Warning, TEXT("Grid size: %d"), Grid.Num());
			//UE_LOG(LogTemp, Warning, TEXT("index = : %d"), GridCellIndex);


			//UE_LOG(LogTemp, Warning, TEXT("i = : %d"), i);
			Grid[GridCellIndex].x = i * cellsize;
			//UE_LOG(LogTemp, Warning, TEXT("x * i = : %d"), Grid[GridCellIndex].x);
		//  UE_LOG(LogTemp, Warning, TEXT("j = : %d"), j);
			Grid[GridCellIndex].y = j * cellsize;
			//UE_LOG(LogTemp, Warning, TEXT("y * i = : %d"), Grid[GridCellIndex].y);

			Grid[GridCellIndex].z = 0;

			Grid[GridCellIndex].CellPositionToSpawnInTheLevel = FVector(Grid[GridCellIndex].x - 400, Grid[GridCellIndex].y - 400, Grid[GridCellIndex].z);

			Grid[GridCellIndex].CellPositionInWorld = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);

			Grid[GridCellIndex].bIsCellOccupied = false;

			Grid[GridCellIndex].Cell = nullptr;

			Grid[GridCellIndex].UniqueID = GridCellIndex;
			
			//This sets wether or not a grid is a border cell.
			if (((j + 1) >= NumberOfGridCells) || (GridCellIndex < NumberOfGridCells) || (GridCellIndex % NumberOfGridCells == 0) || ((i + 1) >= NumberOfGridCells))
			{
				Grid[GridCellIndex].bIsBorderCell = true;
			}

			//UE_LOG(LogTemp, Warning, TEXT("Attribute FVector: X = %f, Y = %f, Z = %f"), Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);

			GridCellIndex++;

		}
	}


}


void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

