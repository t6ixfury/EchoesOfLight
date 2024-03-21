// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawnPoint.generated.h"

class AEnemyCharacter;
class UBoxComponent;



UCLASS()
class ECHOESOFLIGHT_API AEnemySpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemySpawnPoint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Spawn Parameters")
		UBoxComponent* SpawnArea;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn Parameters")
		int32 NumberOfEnemiesSpawned = 0;



	TArray<AEnemyCharacter*> EnemiesSpawned;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	AEnemyCharacter* SpawnEnemy(TSubclassOf<AEnemyCharacter> EnemyClass);


	UFUNCTION()
		FVector FindSpawnPoint();
	
	UFUNCTION()
		void SpawnAllEnemies();

	UFUNCTION()
		bool IsSpawnLocationValid(FVector TestLocation);

};
