// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class E_GridCellWallType : uint8
{
	HallWay UMETA(DisplayName = "Hallway"),
	Wall UMETA(DisplayName = "Wall"),
	DoorWay UMETA(DisplayName = "DoorWay"),
	Entrance UMETA(DisplayName = "Entrance"),
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class E_RoomType : uint8
{
	HallWay UMETA(DisplayName = "Hallway"),
	None UMETA(DisplayName = "None")
	
};