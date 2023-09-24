// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dungeon/ProceduralDungeon.h"
#include "Actors/Dungeon/DungeonGridCell.h"
#include "Math/UnrealMathUtility.h"



//Constructor Function.
AProceduralDungeon::AProceduralDungeon()
{
	NumberOfGridCells = 50;
	GridCellSize = 800.f;
	SetMainRoomsAndHallways();
	CreateGrid(GridCellSize);
	Grid_SpawnAble = Grid;
	//PlaceMainRoom(8);
	//TestGridValues();

}

void AProceduralDungeon::BeginPlay()
{
	Super::BeginPlay();
}

// Randomly Places rooms through dungeon grid.
bool AProceduralDungeon::PlaceMainRoom(int32 RoomsToSpawn)
{
	bool bisRoomsPlaced = false;
	int32 Attempts = 50;

	int32 SpawnedRooms = 0;


	while (SpawnedRooms <= RoomsToSpawn)
	{
		TSubclassOf<ADungeonGridCell> ChosenRoom = ChooseRoomToSpawn();

		FGridCellAttributes ChosenGridCell = ChooseGridToSpawnRoom();

		if (CanRoomBeSpawned(ChosenRoom, ChosenGridCell))
		{
			SpawnedRooms += SpawnRoomDungeonCell(ChosenGridCell, ChosenRoom);
			InitializeDungeonCell(ChosenGridCell);
		}

		else
		{
			Attempts--;
		}
		Attempts--;
	}

	if (RoomsToSpawn == 0)
	{
		bisRoomsPlaced = true;
	}
	
	return bisRoomsPlaced;

}

// Spawns the ADungeonCell Actor and passes the reference to the grid of whats occupying the cell.
int32 AProceduralDungeon::SpawnRoomDungeonCell(FGridCellAttributes &GridCellToInitialize, TSubclassOf<ADungeonGridCell> RoomClassToSpawn)
{
	int32 roomSpawned = 0;

	UWorld* level = GetWorld();

	if ((level != nullptr) && (RoomClassToSpawn != nullptr))
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

		// spawn needs to be changed to the bp class of the main room.
		ADungeonGridCell* NewDungeonCell = level->SpawnActor<ADungeonGridCell>(RoomClassToSpawn, GridCellToInitialize.CellPositionToSpawnInTheLevel, FRotator(0, 0, 0), SpawnParams);

		GridCellToInitialize.Cell = NewDungeonCell;

		roomSpawned = 1;
	}
	
	return roomSpawned;
}
//This function sets the reference of the edge locations for the grid to the cell.
void AProceduralDungeon::InitializeDungeonCell(FGridCellAttributes &GridCell)
{
	if (GridCell.Cell)
	{
		FVector Location = GridCell.CellPositionInWorld;

		GridCell.Cell->CellProperties.Top_EdgeLocation.Start = FVector(Location.X, Location.Y, 0);
		GridCell.Cell->CellProperties.Top_EdgeLocation.End = FVector((Location.X + 1), Location.Y, 0);

		GridCell.Cell->CellProperties.Bottom_EdgeLocation.Start = FVector(Location.X, (Location.Y + GridCellSize), 0);
		GridCell.Cell->CellProperties.Bottom_EdgeLocation.End = FVector((Location.X + 1), (Location.Y +GridCellSize), 0);

		GridCell.Cell->CellProperties.Left_EdgeLocation.Start = FVector(Location.X, Location.Y, 0);
		GridCell.Cell->CellProperties.Left_EdgeLocation.End = FVector(Location.X, (Location.Y + GridCellSize), 0);

		GridCell.Cell->CellProperties.Right_EdgeLocation.Start = FVector((Location.X + 1), Location.Y, 0);
		GridCell.Cell->CellProperties.Right_EdgeLocation.End = FVector((Location.X + 1), (Location.Y + GridCellSize), 0);
	}
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

void AProceduralDungeon::TestGridValues()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grid Size: %f"), Grid.Num());

	for (int i = 0; i < Grid.Num(); i++)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Grid X: %f"), Grid[i].x);
		//UE_LOG(LogTemp, Warning, TEXT("Grid Y: %f"), Grid[i].y);
		//UE_LOG(LogTemp, Warning, TEXT("Grid Z: %f"), Grid[i].z);
		//UE_LOG(LogTemp, Warning, TEXT("Grid  X = %f, Y = %f, Z = %f"), Grid[i].CellPositionToSpawnInTheLevel.X, Grid[i].CellPositionToSpawnInTheLevel.Y, Grid[i].CellPositionToSpawnInTheLevel.Z);

		if (Grid[i].bIsBorderCell)
		{
			UE_LOG(LogTemp, Warning, TEXT("Grid border: %d"), i);
		}
	}
}

TSubclassOf<ADungeonGridCell> AProceduralDungeon::ChooseRoomToSpawn()
{
	int32 RandomValue = FMath::RandRange(0, MainRooms.Num() - 1);

	return MainRooms[RandomValue];
}

FGridCellAttributes AProceduralDungeon::ChooseGridToSpawnRoom()
{
	int32 RandomValue = FMath::RandRange(0, Grid_SpawnAble.Num() - 1);

	return Grid_SpawnAble[RandomValue];
}
//This Function check if the grid cell chosen can have the room that was chosen spawn by checking the space the room takes up is available.
bool AProceduralDungeon::CanRoomBeSpawned(TSubclassOf<ADungeonGridCell> RoomToSpawn, FGridCellAttributes &GridCell)
{
	bool bCanSpawnRoom = false;
	const ADungeonGridCell* Room = GetDefault<ADungeonGridCell>(RoomToSpawn);

	int32 IndexOfGridCell = Grid.Find(GridCell);

	if (Room)
	{
		//If the the room is only 1 grid in size return true
		if (!Room->CellProperties.bDoesTakeMultipleCells)
		{
			GridCell.bIsCellOccupied = true;
			bCanSpawnRoom = true;
			return bCanSpawnRoom;
		}
		//if the room takes multiple grids and the grid cell chosen is a border cell returns false
		else if(Room->CellProperties.bDoesTakeMultipleCells && GridCell.bIsBorderCell)
		{
			bCanSpawnRoom = false;
			return bCanSpawnRoom;
		}
		else
		{
			bCanSpawnRoom = true;
			// Start checking in the x direction going to the left of the possible spawn grid cell.
			for (int i = 0; i < Room->CellProperties.Room_X_Dimensions; i++)
			{
				//moves the index to the left by 1 grid cell size
				int32 newIndex = IndexOfGridCell - (NumberOfGridCells * i);

				//makes sure the index is inbounds of the grid array
				if ((newIndex > Grid.Num()) && (newIndex < 0))
				{
					bCanSpawnRoom = false;
					return bCanSpawnRoom;
				}
				else
				{
					// if the grid cell is occupied it returns false.
					if (Grid[newIndex].bIsCellOccupied)
					{
						bCanSpawnRoom = false;
						return bCanSpawnRoom;
					}
				}

				for (int j = 0; i < Room->CellProperties.Room_Y_Dimensions; j++)
				{
					//moves the index up by 1 grid cell
					int32 newY_Index = newIndex - j;

					//makes sure the index is inbounds of the grid arra
					if ((newY_Index > Grid.Num()) && (newY_Index < 0))
					{
						bCanSpawnRoom = false;
						return bCanSpawnRoom;
					}
					else
					{
						// if the grid cell is occupied it returns false.
						if (Grid[newIndex].bIsCellOccupied)
						{
							bCanSpawnRoom = false;
							return bCanSpawnRoom;
						}
					}
				}
		
			}

		}
		if (bCanSpawnRoom)
		{
			for (int i = 0; i < Room->CellProperties.Room_X_Dimensions; i++)
			{
				int32 newIndex = IndexOfGridCell - (NumberOfGridCells * i);

				if ((newIndex > Grid.Num()) && (newIndex < 0))
				{
					bCanSpawnRoom = false;
					return bCanSpawnRoom;
				}
				else
				{
					//if the cell is not occupied then set it to occupied and remove it from the possible spawning grid cells
					if (Grid[newIndex].bIsCellOccupied == false)
					{
						Grid[newIndex].bIsCellOccupied = true;

						Grid_SpawnAble.RemoveAt(newIndex);
					}
				}

				for (int j = 0; i < Room->CellProperties.Room_Y_Dimensions; j++)
				{
					int32 newY_Index = newIndex - j;

					if ((newY_Index > Grid.Num()) && (newY_Index < 0))
					{
						bCanSpawnRoom = false;
						return bCanSpawnRoom;
					}
					else
					{
						//if the cell is not occupied then set it to occupied and remove it from the possible spawning grid cells
						if (Grid[newY_Index].bIsCellOccupied == false)
						{
							Grid[newY_Index].bIsCellOccupied = true;

							Grid_SpawnAble.RemoveAt(newY_Index);
						}
					}
				}

			}
		}


	}

	return bCanSpawnRoom;
}

