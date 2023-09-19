// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Grid.h"
#include "Actors/GridCell.h"
#include "Engine/StaticMesh.h"


// Sets default values
AGrid::AGrid()
{
	PrimaryActorTick.bCanEverTick = true;

	GridHeight = 0;
	GridWidth = 0;
	GridSize = 0;
	NumberOfGridCells = 5;

}

void AGrid::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid(100);
}

void AGrid::CreateGrid(int32 CellSize)
{
	for (int i = 0; i < NumberOfGridCells; i++)
	{
		for (int j = 0; j < NumberOfGridCells; j++)
		{
			FVector CellPosition = FVector(i * CellSize, j * CellSize, 0);
			UE_LOG(LogTemp, Warning, TEXT("CellPosition: X=%f, Y=%f, Z=%f"), CellPosition.X, CellPosition.Y, CellPosition.Z);
			AGridCell* GridCell = GetWorld()->SpawnActor<AGridCell>(CellPosition, FRotator::ZeroRotator);
			UStaticMeshComponent* MeshComponent = NewObject<UStaticMeshComponent>(GridCell);
			MeshComponent->RegisterComponent();
			GridCell->AddOwnedComponent(MeshComponent);
			MeshComponent->SetVisibility(true);
			MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			MeshComponent->SetStaticMesh(GridCellMesh);
			MeshComponent->SetRelativeScale3D(FVector(CellSize, CellSize, 1));
			GridCell->SetRootComponent(MeshComponent);
			GridCell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

		}
	}
}


void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

