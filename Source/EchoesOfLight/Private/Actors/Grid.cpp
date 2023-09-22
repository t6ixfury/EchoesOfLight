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
	FGridCellAttributes defaultAttributes;
	Grid.Init(defaultAttributes, NumberOfGridCells);

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
}

void AGrid::CreateGrid(int32 CellSize)
{
	for (int i = 0; i < NumberOfGridCells; i++)
	{
		for (int j = 0; j < NumberOfGridCells; j++)
		{
			Grid[i].x = i * CellSize;

			Grid[i].y = i * CellSize;

			Grid[i].z = 0;

			Grid[i].bIsCellOccupied = false;

			Grid[i].Cell = nullptr;


		}
	}
}


void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

