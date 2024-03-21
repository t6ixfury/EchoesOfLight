// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Actors/Dungeon/EnemySpawnPoint.h"
#include "EnemyCharacter.h"

//engine
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"



// Sets default values
AEnemySpawnPoint::AEnemySpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Area"));



}

// Called when the game starts or when spawned
void AEnemySpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnAllEnemies();
}

// Called every frame
void AEnemySpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AEnemyCharacter* AEnemySpawnPoint::SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyClass)
{
	UWorld* World = GetWorld();
	if (EnemyClass && IsValid(World))
	{

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AEnemyCharacter* Enemy = World->SpawnActor<AEnemyCharacter>(EnemyClass, SpawnParameters);

		if (IsValid(Enemy))
		{
			return Enemy;
		}
		else
		{
			return nullptr;
		}

	}
	else
	{
		return nullptr;
	}
}

FVector AEnemySpawnPoint::FindSpawnPoint()
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
void AEnemySpawnPoint::SpawnAllEnemies()
{
	//Check to see if world is valid

}

bool AEnemySpawnPoint::IsSpawnLocationValid(FVector TestLocation)
{
	return true;
}

