// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/GridCellStates.h"
#include "GridEdgeProperties.generated.h"


USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FEdgePoints
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(BlueprintReadOnly, Category = "Edge location properties")
        FVector Start;

    UPROPERTY(BlueprintReadOnly, Category = "Edge location properties")
        FVector End;

};

USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FGridCellProperties
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        FEdgePoints Left_EdgeLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        FEdgePoints Right_EdgeLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        FEdgePoints Top_EdgeLocation;

    UPROPERTY(BlueprintReadOnly, Category = "Grid Cell Side")
        FEdgePoints Bottom_EdgeLocation;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        E_GridCellWallType Left_WallType;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        E_GridCellWallType Right_WallType;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        E_GridCellWallType Top_WallType;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        E_GridCellWallType Bottom_WallType;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        E_RoomType RoomType;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Side")
        int32 Room_X_Dimensions;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Properties")
        int32 Room_Y_Dimensions;

    UPROPERTY(BlueprintReadWrite, Category = "Grid Cell Properties")
        bool bDoesTakeMultipleCells;


    FGridCellProperties()
        :Left_WallType(E_GridCellWallType::None), Right_WallType(E_GridCellWallType::None),
        Top_WallType(E_GridCellWallType::None), Bottom_WallType(E_GridCellWallType::None), RoomType(E_RoomType::None), Room_X_Dimensions(0), 
        Room_Y_Dimensions(0), bDoesTakeMultipleCells(false)
    {}

};
