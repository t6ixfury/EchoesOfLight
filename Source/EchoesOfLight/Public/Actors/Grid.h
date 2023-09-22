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
		int32 x = 0;

	UPROPERTY()
		int32 y = 0;

	UPROPERTY()
		int32 z = 0;

	UPROPERTY()
		bool bIsCellOccupied = false;

	UPROPERTY()
		FVector CellPositionInWorld = FVector(x, y, z);

	UPROPERTY()
		FVector CellPositionToSpawnInTheLevel = FVector((CellPositionInWorld.X -400), (CellPositionInWorld.Y - 400), z);

	UPROPERTY()
		class ADungeonGridCell* Cell;

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



// FOR FUNCTIONS
public:	
	AGrid();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "TEST")
	void CreateGrid(int32 CellSize);

};
