// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/Master_SaveGame.h"
#include "Save_Experience.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API USave_Experience : public UMaster_SaveGame
{
	GENERATED_BODY()

public:
	USave_Experience();

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float sExperience = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		float sExperienceToNextLevel = 100;;

	UPROPERTY(BlueprintReadWrite, Category = "Experience")
		int32 sCurrentLevel = 1;

	
};