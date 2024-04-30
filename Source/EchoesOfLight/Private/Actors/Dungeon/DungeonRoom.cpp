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
						Enemy->level = EnemyLevels;
						Enemy->UpdateStats();
						EnemiesSpawned.Add(Enemy);
						NumberOfEnemiesSpawned += 1;
						OnEnemySpawned.Broadcast(Enemy);
						
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
		FVector SpawnPoint;

		// Define the collision parameters
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(this); // Optionally ignore this actor in collision check

		FCollisionShape MyColSphere = FCollisionShape::MakeSphere(50.0f); // Adjust size as necessary for the character

		bool bFoundSpawnPoint = false;
		const int MaxAttempts = 10; // Maximum number of attempts to find a spawn location

		for (int Attempt = 0; Attempt < MaxAttempts; ++Attempt)
		{
			// Generate a random spawn point
			SpawnPoint = FVector(
				FMath::RandRange(-BoxExtent.X, BoxExtent.X),
				FMath::RandRange(-BoxExtent.Y, BoxExtent.Y),
				FMath::RandRange(-BoxExtent.Z, BoxExtent.Z)
			) + BoxCenter;

			FHitResult Hit; // This will store the result of the collision check
			if (!GetWorld()->SweepSingleByChannel(
				Hit,
				SpawnPoint,
				SpawnPoint + FVector(0.1f, 0.1f, 0.1f), // Small move to ensure we are doing a sweep
				FQuat::Identity,
				ECC_GameTraceChannel1, // The collision channel to check against, change as needed
				MyColSphere,
				CollisionParams
			))
			{
				bFoundSpawnPoint = true;
				break;
			}

		}

		if (bFoundSpawnPoint)
		{
			return SpawnPoint;
		}
	}

	return FVector(); // Return a default FVector if no spawn point is found or no SpawnArea is set
}

bool ADungeonRoom::IsSpawnLocationValid(FVector TestLocation)
{
	return true;
}

