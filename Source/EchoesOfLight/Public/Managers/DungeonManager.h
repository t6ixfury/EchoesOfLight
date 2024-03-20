// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "DungeonManager.generated.h"


class ADungeonRoom;
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

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------


public:

	void GetLevelDungeonRooms();

	virtual void BeginPlay() override;


};
