// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Grid.generated.h"

class AGridCell;

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


		TArray<TArray<AGridCell*>> GridCellArray;


	UPROPERTY(EditAnywhere, Category = "Grid")
		class UStaticMesh* GridCellMesh;


// FOR FUNCTIONS
public:	
	AGrid();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "TEST")
	void CreateGrid(int32 CellSize);

};
