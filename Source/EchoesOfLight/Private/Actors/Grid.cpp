// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grid.h"
#include "Actors/GridCell.h"
#include "Engine/StaticMesh.h"
#include "DrawDebugHelpers.h"
#include "Actors/Dungeon/DungeonGridCell.h"


// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;
	NumberOfGridCells = 0;
	GridCellSize = 800;
	//FGridCellAttributes Attributes;
	//Grid.Init(Attributes, (NumberOfGridCells*NumberOfGridCells));

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AGrid::CreateGrid()
{
	Grid.Empty();

	int32 GridCellIndex = 0;

	UWorld* World = GetWorld();

	for (int i = 0; i < NumberOfGridCells; i++)
	{
		for (int j = 0; j < NumberOfGridCells; j++)
		{
			Grid.Add(FGridCellAttributes());

			Grid[GridCellIndex].x = i * GridCellSize;

			Grid[GridCellIndex].y = j * GridCellSize;

			Grid[GridCellIndex].z = 0;

			Grid[GridCellIndex].CellPositionToSpawnInTheLevel = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);

			Grid[GridCellIndex].Top_EdgeLocation.Start = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y + GridCellSize, Grid[GridCellIndex].z);
			Grid[GridCellIndex].Top_EdgeLocation.End = FVector(Grid[GridCellIndex].x + GridCellSize + GridCellSize, Grid[GridCellIndex].y + GridCellSize, Grid[GridCellIndex].z);

			Grid[GridCellIndex].Bottom_EdgeLocation.Start = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);
			Grid[GridCellIndex].Bottom_EdgeLocation.End = FVector(Grid[GridCellIndex].x + GridCellSize, Grid[GridCellIndex].y, Grid[GridCellIndex].z);

			Grid[GridCellIndex].Right_EdgeLocation.Start = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y + GridCellSize, Grid[GridCellIndex].z);
			Grid[GridCellIndex].Right_EdgeLocation.End = FVector(Grid[GridCellIndex].x + GridCellSize, Grid[GridCellIndex].y + GridCellSize, Grid[GridCellIndex].z);

			Grid[GridCellIndex].Left_EdgeLocation.Start = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);
			Grid[GridCellIndex].Left_EdgeLocation.End = FVector(Grid[GridCellIndex].x, Grid[GridCellIndex].y + GridCellSize, Grid[GridCellIndex].z);


			Grid[GridCellIndex].bIsCellOccupied = false;

			Grid[GridCellIndex].Cell = nullptr;

			Grid[GridCellIndex].UniqueID = GridCellIndex;
			
			//This sets wether or not a grid is a border cell.
			if ((GridCellIndex >= ((NumberOfGridCells * NumberOfGridCells) - NumberOfGridCells)) || (GridCellIndex < NumberOfGridCells) || (GridCellIndex % NumberOfGridCells == 0) || isTopBorderCell(GridCellIndex))
			{
				Grid[GridCellIndex].bIsBorderCell = true;

				//UE_LOG(LogTemp, Warning, TEXT("Attribute FVector: X = %f, Y = %f, Z = %f"), Grid[GridCellIndex].x, Grid[GridCellIndex].y, Grid[GridCellIndex].z);
			}

			if (World)
			{
				FVector BottomLeft = Grid[GridCellIndex].CellPositionToSpawnInTheLevel;
				FVector BottomRight = BottomLeft + FVector(GridCellSize, 0, 0);
				FVector TopLeft = BottomLeft + FVector(0, GridCellSize, 0);
				FVector TopRight = BottomLeft + FVector(GridCellSize, GridCellSize, 0);

				DrawDebugLine(World, BottomLeft, BottomRight, FColor::Green, true, -1, 0, 10);
				DrawDebugLine(World, BottomLeft, TopLeft, FColor::Green, true, -1, 0, 10);
				DrawDebugLine(World, TopLeft, TopRight, FColor::Green, true, -1, 0, 10);
				DrawDebugLine(World, BottomRight, TopRight, FColor::Green, true, -1, 0, 10);
			}
			GridCellIndex++;
		}
	}
	//Grid_SpawnAble = Grid;


}

void AGrid::SetGridSize(int32 gridsize)
{
	NumberOfGridCells = gridsize;
}

//UE_LOG(LogTemp, Warning, TEXT("Grid is %s"), Grid.IsEmpty() ? TEXT("empty") : TEXT("not empty"));
//UE_LOG(LogTemp, Warning, TEXT("Grid size: %d"), Grid.Num());
//UE_LOG(LogTemp, Warning, TEXT("index = : %d"), GridCellIndex);


void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGrid::isTopBorderCell(int x) {
	return (x - (NumberOfGridCells-1)) % NumberOfGridCells == 0 && x >= (NumberOfGridCells-1) && x <= ((NumberOfGridCells*NumberOfGridCells)-1);
}
