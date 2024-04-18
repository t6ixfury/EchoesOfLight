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

USTRUCT(BlueprintType)
struct FGameSaves
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USave_Experience* ExperienceSaveData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USave_PlayerInfo* PlayerInfoSaveData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USave_Inventory* InventorySaveData;
};

DECLARE_MULTICAST_DELEGATE(FGameLoad)

UCLASS()
class ECHOESOFLIGHT_API UEchoesGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Experience* ExperienceData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_PlayerInfo* PlayerInfoData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Inventory* InventoryData;

	FString ExperienceSlot = FString("ExperienceSlot");
	FString PlayerInfoSlot= FString("PlayerInfoslot");
	FString InventoryDataSlot = FString("InventoryDataSlot");

	bool isExpSave = false;
	bool isInfo = false;
	bool isInvData = false;

	FGameLoad PreviousSaveLoadedDelegate;


	void LoadGameData();

	void SaveGameData(USave_Experience* Exp, USave_PlayerInfo* InfoToSave, USave_Inventory* InventorySave);

	UFUNCTION(BlueprintCallable)
	FGameSaves GetGameData();

	virtual void Init() override;



};
