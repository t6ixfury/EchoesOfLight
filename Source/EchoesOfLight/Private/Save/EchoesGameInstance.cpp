// Fill out your copyright notice in the Description page of Project Settings.


#include "Save/EchoesGameInstance.h"
#include "Save/Save_PlayerInfo.h"
#include "Save/Save_Experience.h"
#include "Save/Save_Inventory.h"
#include "Save/Save_Equipment.h"

#include "Kismet/GameplayStatics.h"


void UEchoesGameInstance::LoadGameData()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerInfoSlot, 0))
	{
		if (USave_PlayerInfo* SaveInfo = Cast<USave_PlayerInfo>(UGameplayStatics::LoadGameFromSlot(PlayerInfoSlot, 0)))
		{
			PlayerInfoData = SaveInfo;
			UE_LOG(LogTemp, Warning, TEXT("player info save exist"));
		}
	}

	if (UGameplayStatics::DoesSaveGameExist(InventoryDataSlot, 0))
	{
		if (USave_Inventory* SaveInventory = Cast<USave_Inventory>(UGameplayStatics::LoadGameFromSlot(InventoryDataSlot, 0)))
		{
			InventoryData = SaveInventory;
			UE_LOG(LogTemp, Warning, TEXT("inv save exist"));
		}
	}
	

	if (UGameplayStatics::DoesSaveGameExist(ExperienceSlot, 0))
	{
		if (USave_Experience* SaveExperience = Cast<USave_Experience>(UGameplayStatics::LoadGameFromSlot(ExperienceSlot, 0)))
		{
			ExperienceData = SaveExperience; 
			UE_LOG(LogTemp, Warning, TEXT("exp save exist"));
		}
	}
	if (UGameplayStatics::DoesSaveGameExist(EquipmentDataSlot, 0))
	{
		if (USave_Equipment* SaveEquipment = Cast<USave_Equipment>(UGameplayStatics::LoadGameFromSlot(EquipmentDataSlot, 0)))
		{
			EquipmentData = SaveEquipment;
			UE_LOG(LogTemp, Warning, TEXT("equipment save exist"));
			
			UE_LOG(LogTemp, Warning, TEXT("Amulet id saved: %s"), *SaveEquipment->sAmuletID.ToString());
			
			UE_LOG(LogTemp, Warning, TEXT("weapon id saved: %s"), *SaveEquipment->sWeaponID.ToString());
			
			UE_LOG(LogTemp, Warning, TEXT("netherband id saved: %s"), *SaveEquipment->sNetherbandID.ToString());
		}
	}
}


void UEchoesGameInstance::Init()
{
	Super::Init();

	LoadGameData();
}

