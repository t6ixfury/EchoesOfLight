// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "GameInfo.generated.h"


class UEchoesGameInstance;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API AGameInfo : public AInfo
{
	GENERATED_BODY()

public:

	UPROPERTY()
		FName CurrentDungeonLevel;

	UPROPERTY()
		int32 CurrentDungeonIndex = 0;

	UPROPERTY()
		FName CurrentTownLevel;

	UPROPERTY()
		int32 CurrentTownIndex= 0;

	UFUNCTION()
		void SaveGameInfo(UEchoesGameInstance* GameInstance);

	UFUNCTION()
		void LoadGameInfo(UEchoesGameInstance* GameInstance);

	virtual void BeginPlay() override;
};
