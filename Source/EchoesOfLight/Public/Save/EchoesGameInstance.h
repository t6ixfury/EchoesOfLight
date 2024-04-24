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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USave_Equipment* EquipmentData;

	FString ExperienceSlot = FString("ExperienceSlot");
	FString PlayerInfoSlot= FString("PlayerInfoslot");
	FString InventoryDataSlot = FString("InventoryDataSlot");
	FString EquipmentDataSlot = FString("EquipmentDataSlot");


	void LoadGameData();


	virtual void Init() override;



};
