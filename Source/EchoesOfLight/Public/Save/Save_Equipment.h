// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Save_Equipment.generated.h"




/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API USave_Equipment : public USaveGame
{
	GENERATED_BODY()

public:

    UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
        FName sWeaponID;

    UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
        FName sAmuletID;

    UPROPERTY(VisibleAnywhere, Category = "SaveGameData")
        FName sNetherbandID;

};
