// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/GridCell.h"

// Sets default values
AGridCell::AGridCell()
{
	PrimaryActorTick.bCanEverTick = true;

	CellSize = 0;

	IsCellOccupied = false;


}


void AGridCell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGridCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

