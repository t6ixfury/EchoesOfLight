// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structures/GridEdgeProperties.h"
#include "GridCell.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ECHOESOFLIGHT_API AGridCell : public AActor
{
	GENERATED_BODY()

 //FOR VARIABLES
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Cell Properties")
		int32 CellSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid Cell Properties")
		FGridCellProperties CellProperties;




//FOR FUNCTIONS
public:	

	AGridCell();

	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

};
