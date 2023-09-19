// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/GridCellStates.h"
#include "GridEdgeProperties.generated.h"

USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FGridCellProperties
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        FVector2D EdgeLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        E_GridCellWallType WallType;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        E_RoomType RoomType;


    FGridCellProperties()
        : EdgeLocation(FVector2D::ZeroVector), WallType(E_GridCellWallType::None), RoomType(E_RoomType::HallWay)
    {}

};
