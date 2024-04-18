// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/EchoesGameInstance.h"
#include "Save/Save_PlayerInfo.h"
#include "Save/Save_Experience.h"
#include "Save/Save_Inventory.h"

#include "Kismet/GameplayStatics.h"


void UEchoesGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerInfoSlot, 0))
	{
		if (USave_PlayerInfo* SaveInfo = Cast<USave_PlayerInfo>(UGameplayStatics::LoadGameFromSlot(PlayerInfoSlot, 0)))
		{
			PlayerInfoData = SaveInfo;
			isInfo = true;
			
		}
	}
	else
	{
		PlayerInfoData = NewObject<USave_PlayerInfo>(this, USave_PlayerInfo::StaticClass());
		if (IsValid(PlayerInfoData))
		{
			UGameplayStatics::SaveGameToSlot(PlayerInfoData, PlayerInfoSlot, 0);
		}
	}

	if (UGameplayStatics::DoesSaveGameExist(InventoryDataSlot, 0))
	{
		if (USave_Inventory* SaveInventory = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventoryDataSlot, 0)))
		{
			InventoryData = SaveInventory;
			isInvData = true;
			UE_LOG(LogTemp, Warning, TEXT("inv save"));
		}
	}
	else
	{
		InventoryData = NewObject<USave_Inventory>(this, USave_Inventory::StaticClass());
		if (IsValid(InventoryData))
		{
			UGameplayStatics::SaveGameToSlot(InventoryData, InventoryDataSlot, 0);
		}
	}

	if (UGameplayStatics::DoesSaveGameExist(ExperienceSlot, 0))
	{
		if (USave_Experience* SaveExperience = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(ExperienceSlot, 0)))
		{
			ExperienceData = SaveExperience;
			isExpSave = true;
			UE_LOG(LogTemp, Warning, TEXT("exp save"));
		}
	}
	else
	{
		ExperienceData = NewObject<USave_Experience>(this, USave_Experience::StaticClass());
		if (IsValid(ExperienceData))
		{
			UGameplayStatics::SaveGameToSlot(ExperienceData, ExperienceSlot, 0);
		}
	}
}

void UEchoesGameInstance::SaveGameData(USave_Experience* Exp, USave_PlayerInfo* InfoToSave, USave_Inventory* InventorySave)
{
	if (IsValid(Exp) && IsValid(ExperienceData))
	{
		ExperienceData = Exp;
		UGameplayStatics::SaveGameToSlot(ExperienceData, ExperienceSlot, 0);
	}
	if (IsValid(InfoToSave) && IsValid(PlayerInfoData))
	{
		PlayerInfoData->sPlayerLocation = InfoToSave->sPlayerLocation;
		PlayerInfoData->sPlayerTransform = InfoToSave->sPlayerTransform;
		PlayerInfoData->sPlayerRotation = InfoToSave->sPlayerRotation;
		PlayerInfoData->sHealth = InfoToSave->sHealth;
		PlayerInfoData->sCurrentAmulet = InfoToSave->sCurrentAmulet;
		PlayerInfoData->sCurrentNetherbad = InfoToSave->sCurrentNetherbad;
		PlayerInfoData->sCurrentWeapnStats = InfoToSave->sCurrentWeapnStats;
		PlayerInfoData->sCurrentWeapon = InfoToSave->sCurrentWeapon;

		UGameplayStatics::SaveGameToSlot(PlayerInfoData, PlayerInfoSlot, 0);
	}
	if (IsValid(InventorySave) && IsValid(InventoryData))
	{
		InventoryData = InventorySave;
		UGameplayStatics::SaveGameToSlot(InventoryData, InventoryDataSlot, 0);
	}
}

FGameSaves UEchoesGameInstance::GetGameData()
{
	FGameSaves Saves;
	Saves.ExperienceSaveData = ExperienceData;
	Saves.InventorySaveData = InventoryData;
	Saves.PlayerInfoSaveData = PlayerInfoData;

	return Saves;
}

void UEchoesGameInstance::Init()
{
	Super::Init();

	LoadGameData();
}

