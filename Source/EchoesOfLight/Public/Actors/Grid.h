// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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
		FVector CellPositionInWorld;

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
		CellPositionInWorld = FVector(x, y, z);
		CellPositionToSpawnInTheLevel = FVector(x - 400, y - 400, 0);
	}

};

UCLASS()
class ECHOESOFLIGHT_API AGrid : public AActor
{
	GENERATED_BODY()


//FOR VARIABLES
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Properties")
		int32 GridWidth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Properties")
		int32 GridHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Properties")
		int32 GridSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Grid Properties")
		int32 NumberOfGridCells;

	UPROPERTY(EditAnywhere, Category = "Grid")
		TArray<FGridCellAttributes> Grid;

	UPROPERTY(EditAnywhere, Category = "Grid")
		TArray<FGridCellAttributes> Grid_SpawnAble;




// FOR FUNCTIONS
public:	
	AGrid();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "TEST")
	void CreateGrid(float cellsize);

};
