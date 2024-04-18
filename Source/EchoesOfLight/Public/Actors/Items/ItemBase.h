// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Structures/Structs.h"
#include "Enums/Enums.h"
#include "ItemBase.generated.h"

class AMainCharacter;
class UAC_Inventory;

USTRUCT()
struct FItemSaveInfo
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(VisibleAnywhere, Category = "Item")
		int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemWeaponStatistics ItemWeaponStatistics;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemCharacerStatistics ItemCharacerStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemNumericData ItemNumericaData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemAssData ItemAssetData;
};


/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UItemBase : public UObject
{
	GENERATED_BODY()

public:

	//---------------------------------------------------------------------------------------------------------------------------
	//	PROPERTIES AND VARIABLES
	//---------------------------------------------------------------------------------------------------------------------------

	//meta tag specifies the max and min value of quantity
	UPROPERTY()
		UAC_Inventory* OwningInventory;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		int32 Quantity;  

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FName ID;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemType ItemType;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		EItemQuality ItemQuality;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemStatistics ItemStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemWeaponStatistics ItemWeaponStatistics;

	UPROPERTY(EditAnywhere, Category = "Item")
		FItemCharacerStatistics ItemCharacerStatistics;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemTextData ItemTextData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemNumericData ItemNumericaData;

	UPROPERTY(VisibleAnywhere, Category = "Item")
		FItemAssData ItemAssetData;

	UPROPERTY()
	bool bIsCopy;

	UPROPERTY()
	bool bIsPickup;

	//---------------------------------------------------------------------------------------------------------------------------
	//	FUNCTIONS
	//---------------------------------------------------------------------------------------------------------------------------

	UItemBase();

	void ResetItemFlags();

	//Return a pointer to Item
	UFUNCTION(Category = "Item")
	UItemBase* CreateItemCopy() const;

	//Returns Stack Weight Info
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemStackWeight() const { return Quantity * ItemNumericaData.Weight;};


	//Returns an item's weight
	UFUNCTION(Category = "Item")
	FORCEINLINE float GetItemSingleWeight() const { return ItemNumericaData.Weight;};

	//Returns a boolean wether a item stack size has been reached.
	UFUNCTION(Category = "Item")
	FORCEINLINE bool IsFullItemStack() const { return Quantity == ItemNumericaData.MaxStackSize; };

	//Sets the quantity of an item 
	UFUNCTION(Category = "Item")
	void SetQuantity(const int32 NewQuantity);

	UFUNCTION(Category = "Item")
	virtual void Use(AMainCharacter* Character);

	UFUNCTION(Category = "Item")
		FItemSaveInfo SaveItem(UItemBase* item);
	
	


protected:
	//allows for comparison while using tarray functions
	bool operator==(const FName& OtherId) const
	{
		return this->ID == OtherId;
	}
};
