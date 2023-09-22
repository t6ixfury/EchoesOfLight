// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#pragma once

#include "CoreMinimal.h"


UENUM(BlueprintType)
enum class E_GridCellWallType : uint8
{
	Wall UMETA(DisplayName = "Wall"),
	DoorWay UMETA(DisplayName = "DoorWay"),
	Entrance UMETA(DisplayName = "Entrance"),
	HallWay UMETA(DisplayName = "Hallway"),
	None UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class E_RoomType : uint8
{
	HallWay_FourWay_3x3 UMETA(DisplayName = "HallWay_FourWay_3x3"),
	HallWay_1x1 UMETA(DisplayName = "HallWay_1x1"),
	HallWay_RightTurn_1x1 UMETA(DisplayName = "HallWay_RightTurn_1x1"),
	MainRoomV1_OneDoor UMETA(DisplayName = "MainRoomV1_OneDoor"),
	MainRoomV1_TwoDoor_Parallel UMETA(DisplayName = "MainRoomV1_TwoDoor_Parallel"),
	MainRoomV1_TwoDoor_Perpendicular UMETA(DisplayName = "MainRoomV1_TwoDoor_Perpendicular"),
	MainRoomV1_FourDoor UMETA(DisplayName = "MainRoomV1_FourDoor"),
	MainRoomV2_OneDoor UMETA(DisplayName = "MainRoomV2_OneDoor"),
	MainRoomV2_TwoDoor_Perpendicular UMETA(DisplayName = "MainRoomV2_TwoDoor_Perpendicular"),
	MainRoomV2_TwoDoor_Parallel UMETA(DisplayName = "MainRoomV2_TwoDoor_Parallel"),
	MainRoomV2_FourDoor UMETA(DisplayName = "MainRoomV2_FourDoor"),
	MainRoomV3_OneDoor_Drop UMETA(DisplayName = "MainRoomV3_OneDoor_Drop"),
	MainRoomV3_TwoDoor_Drop UMETA(DisplayName = "MainRoomV3_TwoDoor_Drop"),
	MainRoomV4_OneDoor UMETA(DisplayName = "MainRoomV4_OneDoor"),
	MainRoomV4_TwoDoor_Parallel UMETA(DisplayName = "MainRoomV4_TwoDoor_Parallel"),
	MainRoomV4_TwoDoor_Perpendicular UMETA(DisplayName = "MainRoomV4_TwoDoor_Perpendicular"),
	MainRoomV4_FourDoor UMETA(DisplayName = "MainRoomV4_FourDoor"),
	None UMETA(DisplayName = "None")
	
};