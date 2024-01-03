// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "InputCoreTypes.h"
#include "Structs.generated.h"

/**
 May Delete these structs
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

/*
End of possible Deletable structs
*/

USTRUCT()
struct ECHOESOFLIGHT_API FItemStatistics
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
		float ArmorRating;

	UPROPERTY(EditAnywhere)
		float DamageValue;

	UPROPERTY(EditAnywhere)
		float RestorationAmount;

	UPROPERTY(EditAnywhere)
		float SellValue;

};

USTRUCT()
struct ECHOESOFLIGHT_API FItemTextData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		FText InteractionText;

	UPROPERTY(EditAnywhere)
		FText UsageText;
};

USTRUCT()
struct ECHOESOFLIGHT_API FItemNumericData
{
	GENERATED_USTRUCT_BODY()

		UPROPERTY(EditAnywhere)
		float Weight;

	UPROPERTY(EditAnywhere)
		int32 MaxStackSize;

	UPROPERTY(EditAnywhere)
		bool bisStackable;

};

USTRUCT()
struct ECHOESOFLIGHT_API FItemAssData
{
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere)
		UTexture2D* Icon;

	UPROPERTY(EditAnywhere)
		UStaticMesh* Mesh;

	//UPROPERTY(EditAnywhere)
		//put sound effect here

};

USTRUCT()
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "ItemData")
		FName ID;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		EItemType ItemType;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		EItemQuality ItemQuality;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		FItemStatistics ItemStatistics;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		FItemTextData ItemTextData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		FItemNumericData ItemNumericaData;

	UPROPERTY(EditAnywhere, Category = "ItemData")
		FItemAssData ItemAssetData;
	
};

/// <Iteraction Structs>
	/// 
	/// <Start>

USTRUCT()
struct ECHOESOFLIGHT_API FInteractionData
{
	GENERATED_USTRUCT_BODY()

		FInteractionData() : CurrentInteractable(nullptr), LastInteractionCheckingTime(0.0f) {};

	UPROPERTY()
	AActor* CurrentInteractable;

	UPROPERTY()
	float LastInteractionCheckingTime;

};