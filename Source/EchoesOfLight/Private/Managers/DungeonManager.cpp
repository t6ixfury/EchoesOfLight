// Fill out your copyright notice in the Description page of Project Settings.


//game
#include "Managers/DungeonManager.h"
#include "Actors/Dungeon/DungeonRoom.h"
#include "EnemyCharacter.h"
#include "Actors/Containers/Chest.h"
#include "Actors/Items/AutoCollectPickup.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "Character/MainCharacter.h"

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
				UE_LOG(LogTemp, Warning, TEXT("Array Index : %d"), index);
				Dungeonroom->OnEnemySpawned.AddUObject(this, &ADungeonManager::HandleEnemySpawned);
			}
		}
	}


}

void ADungeonManager::GetAllChest()
{
	UWorld* World = GetWorld();

	TArray<AActor*> FoundActors;

	if (IsValid(World))
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AChest::StaticClass(), FoundActors);

		for (AActor* Actor : FoundActors)
		{
			AChest* Chest = Cast<AChest>(Actor);

			if (Chest)
			{
				int32 index = ChestInDungeon.Add(Chest);
				UE_LOG(LogTemp, Warning, TEXT("Array Index : %d"), index);
				Chest->ChestOpenedDelegate.AddUObject(this, &ADungeonManager::HandleChestOpened);
				NumberOfChestInDungeon += 1;
			}
		}
	}
}

void ADungeonManager::BeginPlay()
{
	Super::BeginPlay();
	if (AMainCharacter* character = Cast<AMainCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		PlayerCharacter = character;
	}
	GetLevelDungeonRooms();
	GetAllChest();
	UE_LOG(LogTemp, Warning, TEXT("Number of Enemies in dungeon: %d"), NumberOfEnemiesInDungeon);
}

void ADungeonManager::HandleEnemyDeath(AEnemyCharacter* NewEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT("Handle Enemy Death Called"));
	NumberOfEnemiesInDungeon = FMath::Clamp(NumberOfEnemiesInDungeon - 1, 0, 100);
	UE_LOG(LogTemp, Warning, TEXT("Number of Enemies in dungeon: %d"), NumberOfEnemiesInDungeon);
	if (NumberOfEnemiesInDungeon < 3 )
	{
		UWorld* World = GetWorld();
		if (World && DungeonKey && NewEnemy)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			World->SpawnActor<AAutoCollectPickup>(DungeonKey, NewEnemy->GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
			UE_LOG(LogTemp, Warning, TEXT("DungeonKeySpawned"));
		}

	}
}

void ADungeonManager::HandleEnemySpawned(AEnemyCharacter* NewEnemy)
{
	if (NewEnemy && PlayerCharacter && !NewEnemy->bIsIntialized)
	{
		NewEnemy->DamageSystem->On_Death.AddDynamic(this, &ADungeonManager::HandleEnemyDeath);
		NewEnemy->DamageSystem->On_Death.AddDynamic(PlayerCharacter, &AMainCharacter::GetExpFromKill);
		NewEnemy->bIsIntialized = true;
		NumberOfEnemiesInDungeon += 1;
		UE_LOG(LogTemp, Warning, TEXT("Handle EnemySpawn Called"));
	}
}

void ADungeonManager::HandleChestOpened(AChest* Chest)
{
	UE_LOG(LogTemp, Warning, TEXT("Handle chest opened Called"));

	NumberOfChestInDungeon = FMath::Clamp(NumberOfChestInDungeon - 1, 0, 100);
}
