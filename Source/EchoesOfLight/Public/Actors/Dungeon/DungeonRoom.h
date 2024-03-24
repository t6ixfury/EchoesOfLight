// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DungeonRoom.generated.h"

class AEnemySpawnPoint;
struct FEnemySpawnArray;
class AEnemyCharacter;
class UBoxComponent;


USTRUCT(BlueprintType)
struct FEnemySpawnArray
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AEnemyCharacter> EnemyType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 NumberOfEnemyTypeToSpawn = 0;

};

UCLASS()
class ECHOESOFLIGHT_API ADungeonRoom : public AActor
{
	GENERATED_BODY()
	
public:	

	DECLARE_MULTICAST_DELEGATE_OneParam(FEnemySpawned, AEnemyCharacter*);
	FEnemySpawned OnEnemySpawned;





	// Sets default values for this actor's properties
	ADungeonRoom();


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
		UBoxComponent* SpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Parameters")
		int32 NumberOfEnemiesSpawned = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Parameters")
		TArray<FEnemySpawnArray> EnemyTypesToSpawn;



	TArray<AEnemyCharacter*> EnemiesSpawned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnAllEnemies();

	UFUNCTION()
		FVector FindSpawnPoint();

	UFUNCTION()
		bool IsSpawnLocationValid(FVector TestLocation);


	





};
