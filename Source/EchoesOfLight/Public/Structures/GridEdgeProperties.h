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

    UPROPERTY(BlueprintReadOnly, Category = "Edge location properties")
        FVector Midpoint = (Start + End) * 0.5f;

};

USTRUCT(BlueprintType, Blueprintable)
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

    


    FGridCellProperties()
    {}

};
