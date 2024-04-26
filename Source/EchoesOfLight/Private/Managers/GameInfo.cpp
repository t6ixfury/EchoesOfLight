// Fill out your copyright notice in the Description page of Project Settings.


#include "Managers/GameInfo.h"
#include "Save/Master_SaveGame.h"
#include "Save/EchoesGameInstance.h"
#include "Kismet/GameplayStatics.h"

void AGameInfo::SaveGameInfo(UEchoesGameInstance* GameInstance)
{
	if (GameInstance)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameInstance exist"));
		if (UMaster_SaveGame* SaveGameInfo = NewObject<UMaster_SaveGame>(this, UMaster_SaveGame::StaticClass()))
		{
			SaveGameInfo->sCurrentDungeonLevel = CurrentDungeonLevel;
			SaveGameInfo->sCurrentTownVariation = CurrentTownLevel;
			SaveGameInfo->sCurrentDungeonIndex = CurrentDungeonIndex;
			SaveGameInfo->sCurrentTownIndex = CurrentTownIndex;

			UGameplayStatics::SaveGameToSlot(SaveGameInfo, GameInstance->GameInfoDataSlot, 0);
			UE_LOG(LogTemp, Warning, TEXT("Game Info saved"));
		}
	}
}

void AGameInfo::LoadGameInfo(UEchoesGameInstance* GameInstance)
{
	if (GameInstance)
	{
		if (UGameplayStatics::DoesSaveGameExist(GameInstance->GameInfoDataSlot, 0))
		{
			if (UMaster_SaveGame* SaveGameInfo = Cast<UMaster_SaveGame>(UGameplayStatics::LoadGameFromSlot(GameInstance->GameInfoDataSlot, 0)))
			{
				CurrentDungeonLevel = SaveGameInfo->sCurrentDungeonLevel;
				CurrentTownLevel = SaveGameInfo->sCurrentTownVariation;
				CurrentDungeonIndex = SaveGameInfo->sCurrentDungeonIndex;
				CurrentTownIndex = SaveGameInfo->sCurrentTownIndex;
			}
		}
	}
}

void AGameInfo::BeginPlay()
{
	Super::BeginPlay();

	if (UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		LoadGameInfo(GameInstance);
	}
}
