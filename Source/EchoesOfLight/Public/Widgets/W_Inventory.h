// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Inventory.generated.h"

/**
 * 
 */
class UAC_Inventory;
class W_InventorySlot;


UCLASS()
class ECHOESOFLIGHT_API UW_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UUniformGridPanel* InventoryGrid;

	UPROPERTY(BlueprintReadWrite)
		int32 Index = 0;

	UPROPERTY(BlueprintReadWrite)
		bool bIsInventoryFull = false;

	virtual void NativeConstruct() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpDate_CustomEvent);
	FUpDate_CustomEvent Update;

	UFUNCTION()
	void OnUpdate();

	UFUNCTION()
		void AddItemToInventoryWidget(AItem* Item);

	UFUNCTION()
		int32 FindOpenSlot();

	UFUNCTION()
		void RemoveItemFromInventoryWidget(AItem* Item);



};
