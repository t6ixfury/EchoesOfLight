// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "Enums/E_DamageType.h"
#include "InputCoreTypes.h"
#include "Structs.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FS_Item
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName Name;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		E_Global_Systems UsageType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		 E_Damage_Type DamageType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<AActor> Class;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName HandSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName BackSocket;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Picture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool isWeapon;
/*Might Delete*/
	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMesh* Mesh;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		USkeletalMesh* WeaponSkMesh;
*/


};

USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FS_GameSettings
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShowPathInWorldMarker;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 PathDivider;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxLocationRenderLength;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MinLocationRenderPoint;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 SecToHoldFastTravel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FKey HoldKeyInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FKey HoldKeyFastTravel;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		E_UnLock_Type UnlockType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LevelMultiplayer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText UndescoveredAreaName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FLinearColor TaskDoneColor;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bHideMap;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RemoveItemIconDelay;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* ChooseTaskIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* UnChooseTaskIcon;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float RenderWorldWidget;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxInventoryColumns;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bStopGameTimeWhenPauseMenu;




};

