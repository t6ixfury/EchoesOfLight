// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/EchoesGameInstance.h"
#include "Save/Save_PlayerInfo.h"
#include "Save/Save_Experience.h"
#include "Save/Save_Inventory.h"
#include "Save/Save_Equipment.h"
#include "Save/Master_SaveGame.h"
#include "Managers/GameInfo.h"
#include "Character/MainCharacter.h"
#include "Character/MainCharacterPlayerController.h"

#include "Kismet/GameplayStatics.h"

void UEchoesGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerInfoSlot, 0))
	{
		if (USave_PlayerInfo* SaveInfo = Cast<USave_PlayerInfo>(UGameplayStatics::LoadGameFromSlot(PlayerInfoSlot, 0)))
		{
			PlayerInfoData = SaveInfo;
			//UE_LOG(LogTemp, Warning, TEXT("player info save exist"));
		}
	}

	if (UGameplayStatics::DoesSaveGameExist(InventoryDataSlot, 0))
	{
		if (USave_Inventory* SaveInventory = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventoryDataSlot, 0)))
		{
			InventoryData = SaveInventory;
			//UE_LOG(LogTemp, Warning, TEXT("inv save exist"));
		}
	}
	

	if (UGameplayStatics::DoesSaveGameExist(ExperienceSlot, 0))
	{
		if (USave_Experience* SaveExperience = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(ExperienceSlot, 0)))
		{
			ExperienceData = SaveExperience; 
		//	UE_LOG(LogTemp, Warning, TEXT("exp save exist"));
		}
	}
	if (UGameplayStatics::DoesSaveGameExist(EquipmentDataSlot, 0))
	{
		if (USave_Equipment* SaveEquipment = Cast<USave_Equipment>(UGameplayStatics::LoadGameFromSlot(EquipmentDataSlot, 0)))
		{
			EquipmentData = SaveEquipment;
			
		}
	}
	if (UGameplayStatics::DoesSaveGameExist(GameInfoDataSlot, 0))
	{
		if (UMaster_SaveGame* SaveGameInfo = Cast<UMaster_SaveGame>(UGameplayStatics::LoadGameFromSlot(GameInfoDataSlot, 0)))
		{
			GameInfoData = SaveGameInfo;

		}
	}
}


void UEchoesGameInstance::Init()
{
	Super::Init();

	LoadGameData();
	SetTownAndDungeonNames();
	SetGameInfo();
}

void UEchoesGameInstance::SetTownAndDungeonNames()
{
	//all town variation level names
	TownLevels.Add(FName("Town_0_No_Foliage_Start"));
	TownLevels.Add(FName("Town_1_No_Windmill_No_Farm"));
	TownLevels.Add(FName("Town_2_No_MagicTower_No_Market"));
	TownLevels.Add(FName("Town_3_No_House5"));
	TownLevels.Add(FName("Town_4_No_House4"));
	TownLevels.Add(FName("Town_5_No_House3"));
	TownLevels.Add(FName("Town_6_No_House2"));
	TownLevels.Add(FName("Town_7_No_House1"));
	TownLevels.Add(FName("Town_8_No_House"));
	TownLevels.Add(FName("Town_9_No_Inn"));
	TownLevels.Add(FName("Town_10"));

	//All Dungeon Level Names
	DungeonLevels.Add(FName("Dungeon_1"));
	DungeonLevels.Add(FName("Dungeon_02"));
	DungeonLevels.Add(FName("Dungeon_3"));
	DungeonLevels.Add(FName("Dungeon_4"));
	DungeonLevels.Add(FName("Dungeon_5"));
	DungeonLevels.Add(FName("Dungeon_06"));
	DungeonLevels.Add(FName("Dungeon_07"));
	DungeonLevels.Add(FName("Dungeon_08"));
	DungeonLevels.Add(FName("Dungeon_09"));
	DungeonLevels.Add(FName("Dungeon_10"));

}

void UEchoesGameInstance::SetGameInfo()
{
	GameInfo = NewObject<AGameInfo>(this, AGameInfo::StaticClass());
	if (GameInfo)
	{
		if (GameInfoData)
		{
			GameInfo->CurrentDungeonIndex = GameInfoData->sCurrentDungeonIndex;
			GameInfo->CurrentTownIndex = GameInfoData->sCurrentTownIndex;
			GameInfo->CurrentDungeonLevel = GameInfoData->sCurrentDungeonLevel;
			GameInfo->CurrentTownLevel = GameInfoData->sCurrentTownVariation;
		}
	}
}

void UEchoesGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);

	if (OldWorld != nullptr)
	{
	}

	if (NewWorld != nullptr)
	{
		if (GameInfo)
		{
			GameInfo->SaveGameInfo(this);
		}
	}


}


