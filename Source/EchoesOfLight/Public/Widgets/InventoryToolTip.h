// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryToolTip.generated.h"


class UW_InventorySlot;
class UTextBlock;


/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UInventoryToolTip : public UUserWidget
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
public:
	//values come from ItemData

	UPROPERTY(VisibleAnywhere)
	UW_InventorySlot* InventorySlotBeingHovered;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemType;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ArmorRating;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* UsageText;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxStackSize;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* SellValue;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* StackWeight;

protected:


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:

	virtual void NativeConstruct() override;

};
