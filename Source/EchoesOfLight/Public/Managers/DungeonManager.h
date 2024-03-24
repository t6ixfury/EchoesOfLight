// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "DungeonManager.generated.h"


class ADungeonRoom;
class AEnemyCharacter;
class AChest;

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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Properties")
		TArray<AEnemyCharacter*> EnemiesInDungeon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Properties")
		TArray<AChest*> ChestInDungeon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Properties")
		int32 NumberOfEnemiesInDungeon = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dungeon Properties")
		int32 NumberOfChestInDungeon = 0;


	


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------


public:


	void GetLevelDungeonRooms();

	void GetAllChest();

	virtual void BeginPlay() override;

	UFUNCTION()
		void HandleEnemyDeath();

	void HandleEnemySpawned(AEnemyCharacter* NewEnemy);

	void HandleChestOpened(AChest* Chest);


};
