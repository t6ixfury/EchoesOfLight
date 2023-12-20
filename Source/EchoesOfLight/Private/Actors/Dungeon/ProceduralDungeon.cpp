// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dungeon/ProceduralDungeon.h"
#include "Actors/Dungeon/DungeonGridCell.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Actors/Grid.h"



//Constructor Function.
AProceduralDungeon::AProceduralDungeon()
{
	RoomSpacing = 1;
	numberOfRoomsToSpawn = FMath::RandRange(7, 10);
	gridSize = 50;
	SetMainRoomsAndHallways();
	DungeonGrid = CreateDefaultSubobject<AGrid>(TEXT("Dungeon Grid"));
	DungeonGrid->SetGridSize(gridSize);
	DungeonGrid->CreateGrid();
	GridCellSize = DungeonGrid->GetGridCellSize();
}

void AProceduralDungeon::BeginPlay()
{
	Super::BeginPlay();

	PlaceRoomsOnGrid();

	DrawOccupiedCells();
//	TestGridValues();
}



// Set the Values for the Hallways and MainRooms array.
void AProceduralDungeon::SetMainRoomsAndHallways()
{
	/*
	* ADDING HALLWAYS
	*/
	//Adds the bp_hallway
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> HallwayBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/Hallways(1x1)/BP_Hallway.BP_Hallway_C"));
	if (HallwayBPClass.Succeeded())
	{	
		Hallways.Add(HallwayBPClass.Class);
	}
	//addsthe bp_rightturn hallway
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> HallwayRightTurnBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/Hallways(1x1)/BP_Rightturn.BP_Rightturn_C"));
	if (HallwayRightTurnBPClass.Succeeded())
	{
		Hallways.Add(HallwayRightTurnBPClass.Class);
	}
	//Adds the bp_fourway hallway
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> HallwayFourWayBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/Hallways(1x1)/BP_FourWay_3x3.BP_FourWay_3x3_C"));
	if (HallwayFourWayBPClass.Succeeded())
	{
		Hallways.Add(HallwayFourWayBPClass.Class);
	}

	/*
	* ADDING MAINROOMS
	*/

	//Added mainroomv1_onedoor to the mainrooms array
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV1_OneDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V1(3x3)/BP_MainRoomV1_OneDoor.BP_MainRoomV1_OneDoor_C"));
	if (MainRoomV1_OneDoorBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV1_OneDoorBPClass.Class);
	}

	//add BP_MainRoomV1_TwoDoor_Parallel
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV1_TwoDoor_ParallelBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V1(3x3)/BP_MainRoomV1_TwoDoor_Parallel.BP_MainRoomV1_TwoDoor_Parallel_C"));
	if (MainRoomV1_TwoDoor_ParallelBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV1_TwoDoor_ParallelBPClass.Class);
	}

	//add BP_MainRoomV1_TwoDoor_Perpendicular
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV1_TwoDoor_PerpendicularBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V1(3x3)/BP_MainRoomV1_TwoDoor_Perpendicular.BP_MainRoomV1_TwoDoor_Perpendicular_C"));
	if (MainRoomV1_TwoDoor_PerpendicularBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV1_TwoDoor_PerpendicularBPClass.Class);
	}

	//add BP_MainRoomV1_FourDoor
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV1_FourDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V1(3x3)/BP_MainRoomV1_FourDoor.BP_MainRoomV1_FourDoor_C"));
	if (MainRoomV1_FourDoorBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV1_FourDoorBPClass.Class);
	}

	//add BP_MainRoomV2_OneDoor
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV2_OneDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V2(9x9)/BP_MainRoomV2_OneDoor.BP_MainRoomV2_OneDoor_C"));
	if (MainRoomV2_OneDoorBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV2_OneDoorBPClass.Class);
	}

	//add BP_MainRoomV2_TwoDoor_Parallel
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV2_TwoDoor_ParallelBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V2(9x9)/BP_MainRoomV2_TwoDoor_Parallel.BP_MainRoomV2_TwoDoor_Parallel_C"));
	if (MainRoomV2_TwoDoor_ParallelBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV2_TwoDoor_ParallelBPClass.Class);
	}

	//add BP_MainRoomV2_TwoDoor_Perpendicular
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV2_TwoDoor_PerpendicularBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V2(9x9)/BP_MainRoomV2_TwoDoor_Perpendicular.BP_MainRoomV2_TwoDoor_Perpendicular_C"));
	if (MainRoomV2_TwoDoor_PerpendicularBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV2_TwoDoor_PerpendicularBPClass.Class);
	}

	//add BP_MainRoomV2_FourDoor
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> BP_MainRoomV2_FourDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V2(9x9)/BP_MainRoomV2_FourDoor.BP_MainRoomV2_FourDoor_C"));
	if (BP_MainRoomV2_FourDoorBPClass.Succeeded())
	{
		MainRooms.Add(BP_MainRoomV2_FourDoorBPClass.Class);
	}

	//add BP_MainRoomV3_OneDoor_Drop
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV3_OneDoor_DropBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V3(9x9)/BP_MainRoomV3_OneDoor_Drop.BP_MainRoomV3_OneDoor_Drop_C"));
	if (MainRoomV3_OneDoor_DropBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV3_OneDoor_DropBPClass.Class);
	}

	//add BP_MainRoomV3_TwoDoor_Drop
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV3_TwoDoor_DropBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V3(9x9)/BP_MainRoomV3_TwoDoor_Drop.BP_MainRoomV3_TwoDoor_Drop_C"));
	if (MainRoomV3_TwoDoor_DropBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV3_TwoDoor_DropBPClass.Class);
	}

	//add BP_MainRoomV4_OneDoor
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV4_OneDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V4(5x5)/BP_MainRoomV4_OneDoor.BP_MainRoomV4_OneDoor_C"));
	if (MainRoomV4_OneDoorBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV4_OneDoorBPClass.Class);
	}

	//add BP_MainRoomV4_TwoDoor_Parallel
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV4_TwoDoor_ParallelBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V4(5x5)/BP_MainRoomV4_TwoDoor_Parallel.BP_MainRoomV4_TwoDoor_Parallel_C"));
	if (MainRoomV4_TwoDoor_ParallelBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV4_TwoDoor_ParallelBPClass.Class);
	}

	//add BP_MainRoomV4_TwoDoor_Perpendicular
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV4_TwoDoor_PerpendicularBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V4(5x5)/BP_MainRoomV4_TwoDoor_Perpendicular.BP_MainRoomV4_TwoDoor_Perpendicular_C"));
	if (MainRoomV4_TwoDoor_PerpendicularBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV4_TwoDoor_PerpendicularBPClass.Class);
	}

	//add BP_MainRoomV4_FourDoor
	static ConstructorHelpers::FClassFinder<ADungeonGridCell> MainRoomV4_FourDoorBPClass(TEXT("/Game/Dungeon/Dungeon_Pieces/MainRoom_V4(5x5)/BP_MainRoomV4_FourDoor.BP_MainRoomV4_FourDoor_C"));
	if (MainRoomV4_FourDoorBPClass.Succeeded())
	{
		MainRooms.Add(MainRoomV4_FourDoorBPClass.Class);
	}






}

//Selects a room to spawn out of the MainRooms
TSubclassOf<ADungeonGridCell> AProceduralDungeon::MainRoomToSpawn()
{
	int32 index = FMath::RandRange(0, MainRooms.Num() - 1);

	return MainRooms[index];
}

void AProceduralDungeon::PlaceRoomsOnGrid()
{
	int32 attempts = 50;

	//UE_LOG(LogTemp, Warning, TEXT("index: %d"), index);

	while (numberOfRoomsToSpawn > 0 && attempts > 0)
	{
		TSubclassOf<ADungeonGridCell> roomToSpawn = MainRoomToSpawn();

		int32 index = GridCellToSpawnOn(roomToSpawn);

		if (index != -1)
		{
			SpawnRoom(roomToSpawn, DungeonGrid->Grid[index]);
			numberOfRoomsToSpawn--;
		}

		attempts--;
	}
	
}

void AProceduralDungeon::SpawnRoom(TSubclassOf<ADungeonGridCell> roomToSpawn, FGridCellAttributes currentCell)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return; // or handle the error
	}

	
	if (roomToSpawn)
	{
		FActorSpawnParameters spawnParameter;

		spawnParameter.Owner = this;

		currentCell.Cell = World->SpawnActor<ADungeonGridCell>(roomToSpawn, currentCell.CellPositionToSpawnInTheLevel, FRotator(0, 0, 0), spawnParameter);
	}

}

int32 AProceduralDungeon::GridCellToSpawnOn(TSubclassOf<ADungeonGridCell> roomToSpawn)
{
	int32 index = FMath::RandRange(0, DungeonGrid->Grid.Num() - 1);



	bool hasIndex = true;

	int32 attempts = 1000;


	while (hasIndex)
	{
		if (CanRoomFitAtGridCell(roomToSpawn, index))
		{
			MarkCellsAsUsed(roomToSpawn, index);

			return index;
		}
		else
		{
			index = FMath::RandRange(0, DungeonGrid->Grid.Num() - 1);
		}

		if (attempts < 0)
		{
			hasIndex = false;
		}

		attempts--;
	}
	return -1;
}

bool AProceduralDungeon::CanRoomFitAtGridCell(TSubclassOf<ADungeonGridCell> roomToSpawn, int32 index)
{
	if (DungeonGrid->Grid[index].bIsCellOccupied || index < 0 || index > DungeonGrid->Grid.Num())
	{
		return false;
	}


	if (roomToSpawn)
	{
		ADungeonGridCell* roomToPlace = roomToSpawn->GetDefaultObject<ADungeonGridCell>();


		if (roomToPlace)
		{

			int32 width = roomToPlace->Room_X_Dimensions + RoomSpacing;
			int32 length = roomToPlace->Room_Y_Dimensions + RoomSpacing;

			int32 indexRef = index;

			for (int32 w = 0; w < width; w++)
			{
				for (int32 l = 0; l < length; l++)
				{
					if ((indexRef > DungeonGrid->Grid.Num() - 1 || indexRef < 0) || DungeonGrid->Grid[indexRef].bIsCellOccupied || (DungeonGrid->Grid[indexRef].bIsBorderCell && (l + 1) < length))
					{
						return false;
					}
					indexRef++; // move to the next cell in the same column
				}
				indexRef += 50 - length; // move to the starting cell of the next column
			}

		}
	}

	return true;
}

void AProceduralDungeon::MarkCellsAsUsed(TSubclassOf<ADungeonGridCell> roomToSpawn, int32 index)
{
	if (roomToSpawn)
	{
		ADungeonGridCell* roomToPlace = roomToSpawn->GetDefaultObject<ADungeonGridCell>();


		if (roomToPlace)
		{

			int32 width = roomToPlace->Room_X_Dimensions + RoomSpacing;
			int32 length = roomToPlace->Room_Y_Dimensions + RoomSpacing;

			int32 indexRef = index;

			for (int32 w = 0; w < width; w++)
			{
				for (int32 l = 0; l < length; l++)
				{
					DungeonGrid->Grid[indexRef].bIsCellOccupied = true;
					indexRef++; // move to the next cell in the same column
				}
				indexRef += 50 - length; // move to the starting cell of the next column
			}
		}
	}
}
void AProceduralDungeon::TestGridValues()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grid Size: %f"), Grid.Num());

	for (int i = 0; i < DungeonGrid->Grid.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Grid X: %f"), Grid[i].x);
		//UE_LOG(LogTemp, Warning, TEXT("Grid Y: %f"), Grid[i].y);
		//UE_LOG(LogTemp, Warning, TEXT("Grid Z: %f"), Grid[i].z);
		UE_LOG(LogTemp, Warning, TEXT("Grid  X = %f, Y = %f, Z = %f"), DungeonGrid->Grid[i].CellPositionToSpawnInTheLevel.X, DungeonGrid->Grid[i].CellPositionToSpawnInTheLevel.Y, DungeonGrid->Grid[i].CellPositionToSpawnInTheLevel.Z);

		UE_LOG(LogTemp, Warning, TEXT("Cell Occupied State: %s"), DungeonGrid->Grid[i].bIsCellOccupied ? TEXT("True") : TEXT("False"));


		if (DungeonGrid->Grid[i].bIsBorderCell)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid border: %d"), i);
		}
	}
}


void AProceduralDungeon::DrawOccupiedCells()
{
	if (!DungeonGrid) return;  // Ensure DungeonGrid is valid

	const float SphereRadius = 50.0f;  // Adjust this value as needed
	const FColor SphereColor = FColor::Red;
	const float Duration = 30.0f;  // How long the sphere will be visible

	for (int32 i = 0; i < DungeonGrid->Grid.Num(); i++)
	{
		if (DungeonGrid->Grid[i].bIsCellOccupied)
		{
			FVector CellLocation = DungeonGrid->Grid[i].CellPositionToSpawnInTheLevel;  // Assuming your grid cells have a Location member variable
			DrawDebugSphere(GetWorld(), CellLocation, SphereRadius, 12, SphereColor, false, Duration);
		}
	}
}
