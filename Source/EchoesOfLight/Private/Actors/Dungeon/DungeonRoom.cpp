// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Dungeon/DungeonRoom.h"
#include "EnemyCharacter.h"


//engine 
#include "Components/ChildActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"



// Sets default values
ADungeonRoom::ADungeonRoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	RootComponent = Root;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));

	SpawnArea->SetupAttachment(RootComponent);




}

// Called when the game starts or when spawned
void ADungeonRoom::BeginPlay()
{
	Super::BeginPlay();

	SpawnAllEnemies();
	
}

// Called every frame
void ADungeonRoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADungeonRoom::SpawnAllEnemies()
{
	//Check to see if world is valid
	UWorld* World = GetWorld();
	if (World)
	{
		//Go through every index of Enemytypes to spawn to spawn the enemies set
		for (FEnemySpawnArray EnemyInfo : EnemyTypesToSpawn)
		{
			for (int32 EnemyToSpawn = 0; EnemyToSpawn < EnemyInfo.NumberOfEnemyTypeToSpawn; EnemyToSpawn++)
			{
				//Get location to spawn
				FVector SpawnLocation = FindSpawnPoint();

				UE_LOG(LogTemp, Log, TEXT("Spawn Location: X=%f, Y=%f, Z=%f"), SpawnLocation.X, SpawnLocation.Y, SpawnLocation.Z);

				//Check if the location is valid and the class is set.
				if (IsSpawnLocationValid(SpawnLocation) && EnemyInfo.EnemyType)
				{
					//Spawn the enemy
					FActorSpawnParameters SpawnParams;
					SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

					AEnemyCharacter* Enemy = World->SpawnActor<AEnemyCharacter>(EnemyInfo.EnemyType, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

					//check is spawn was successful and if so add it to the array and increment Numbers of enemies spawned;
					if (Enemy)
					{
						EnemiesSpawned.Add(Enemy);
						NumberOfEnemiesSpawned += 1;
					}
				}


			}
		}
	}
}

FVector ADungeonRoom::FindSpawnPoint()
{
	if (SpawnArea)
	{
		FVector BoxExtent = SpawnArea->GetScaledBoxExtent();

		FVector BoxCenter = SpawnArea->GetComponentLocation();

		FVector SpawnPoint = FVector(
			FMath::RandRange(-BoxExtent.X, BoxExtent.X),
			FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
			FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
		);

		SpawnPoint += BoxCenter;

		return SpawnPoint;
	}
	else
	{
		return FVector();
	}
}

bool ADungeonRoom::IsSpawnLocationValid(FVector TestLocation)
{
	return true;
}
