// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/GridEdgeProperties.h"
#include "Grid.generated.h"



USTRUCT()
struct FGridCellAttributes
{
	GENERATED_BODY()

	UPROPERTY()
		int32 UniqueID = 0;

	UPROPERTY()
		float x = 0;

	UPROPERTY()
		float y = 0;

	UPROPERTY()
		float z = 0;

	UPROPERTY()
		bool bIsCellOccupied = false;

	UPROPERTY()
		bool bIsBorderCell = false;

	UPROPERTY()
		FEdgePoints Left_EdgeLocation;

	UPROPERTY()
		FEdgePoints Right_EdgeLocation;

	UPROPERTY()
		FEdgePoints Top_EdgeLocation;

	UPROPERTY()
		FEdgePoints Bottom_EdgeLocation;


	UPROPERTY()
		FVector CellPositionToSpawnInTheLevel;


	UPROPERTY()
		class ADungeonGridCell* Cell;

	bool operator==(const FGridCellAttributes& Other) const
	{
		// Compare based on UniqueID
		return UniqueID == Other.UniqueID;
	}

	FGridCellAttributes()
	{
		CellPositionToSpawnInTheLevel = FVector(x, y, z);
	}

};

UCLASS()
class ECHOESOFLIGHT_API AGrid : public AActor
{
	GENERATED_BODY()


//FOR VARIABLES
public:

	UPROPERTY(EditAnywhere, Category = "Grid")
		TArray<FGridCellAttributes> Grid;

	//UPROPERTY(EditAnywhere, Category = "Grid")
		//TArray<FGridCellAttributes> Grid_SpawnAble;

private:

	UPROPERTY(VisibleAnywhere, Category = "Grid Properties")
		int32 NumberOfGridCells;

	UPROPERTY(VisibleAnywhere, Category = "Grid Properties")
		float GridCellSize;


// FOR FUNCTIONS
public:	
	AGrid();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION()
	void CreateGrid();

	UFUNCTION()
	void SetGridSize(int32 gridsize);

	UFUNCTION()
	float GetGridCellSize() { return GridCellSize;};

	bool isTopBorderCell(int x);

};
