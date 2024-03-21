// Fill out your copyright notice in the Description page of Project Settings.


//game
#include "Managers/DungeonManager.h"
#include "Actors/Dungeon/DungeonRoom.h"
#include "Actors/Dungeon/EnemySpawnPoint.h"

//engine
#include "Kismet/GameplayStatics.h"


void ADungeonManager::GetLevelDungeonRooms()
{
	UWorld* World = GetWorld();

	TArray<AActor*> FoundActors;

	if (IsValid(World))
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ADungeonRoom::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			ADungeonRoom* Dungeonroom = Cast<ADungeonRoom>(Actor);

			if (Dungeonroom)
			{
				int32 index = DungeonRooms.Add(Dungeonroom);
				UE_LOG(LogTemp, Warning, TEXT("Array Index : %d"), index)
			}
		}
	}


}

void ADungeonManager::SpawnAllEnemies()
{
}

void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();

	GetLevelDungeonRooms();
}
