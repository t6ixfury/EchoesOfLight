// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EchoesGameInstance.generated.h"

/**
 * 
 */
class USave_Experience;
class USave_PlayerInfo;
class USave_Inventory;
class USave_Equipment;
class UMaster_SaveGame;
class UW_LoadScreen;
class AGameInfo;


DECLARE_MULTICAST_DELEGATE(FGameLoad)

UCLASS()
class ECHOESOFLIGHT_API UEchoesGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Experience* ExperienceData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_PlayerInfo* PlayerInfoData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Inventory* InventoryData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Equipment* EquipmentData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaster_SaveGame* GameInfoData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UW_LoadScreen* LoadScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UW_LoadScreen> LoadScreenClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> TownLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FName> DungeonLevels;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AGameInfo* GameInfo = nullptr;


	FString ExperienceSlot = FString("ExperienceSlot");
	FString PlayerInfoSlot= FString("PlayerInfoslot");
	FString InventoryDataSlot = FString("InventoryDataSlot");
	FString EquipmentDataSlot = FString("EquipmentDataSlot");
	FString GameInfoDataSlot = FString("GameInfoDataSlot");

	void LoadGameData();

	void SetTownAndDungeonNames();

	void SetGameInfo();


	virtual void Init() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;




private:
	// Timer handle for the repeating function
	UPROPERTY()
		FTimerHandle UpdateProgressBarTimerHandle;





};
