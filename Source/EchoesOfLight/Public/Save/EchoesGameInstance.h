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
class UW_LoadScreen;


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UW_LoadScreen* LoadScreen;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UW_LoadScreen> LoadScreenClass;

	FString ExperienceSlot = FString("ExperienceSlot");
	FString PlayerInfoSlot= FString("PlayerInfoslot");
	FString InventoryDataSlot = FString("InventoryDataSlot");
	FString EquipmentDataSlot = FString("EquipmentDataSlot");

	void LoadGameData();


	virtual void Init() override;




private:
	// Timer handle for the repeating function
	UPROPERTY()
		FTimerHandle UpdateProgressBarTimerHandle;





};
