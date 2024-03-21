// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "DungeonManager.generated.h"


class ADungeonRoom;
class AEnemyCharacter;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API ADungeonManager : public AInfo
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:

	UPROPERTY()
		TArray<ADungeonRoom*> DungeonRooms;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dungeon Properties")
		TArray <TSubclassOf<AEnemyCharacter>> EnemiesToSpawn;

	TArray<AEnemyCharacter*> EnemiesInDungeon;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------


public:

	void GetLevelDungeonRooms();

	void SpawnAllEnemies();

	virtual void BeginPlay() override;


};
