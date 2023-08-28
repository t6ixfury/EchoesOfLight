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
	int32 CurrentColumn;

	int32 CurrentRow;

	int32 MaxNumberOfColumns;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
		class UUniformGridPanel* InventoryGrid;

	TSubclassOf<UAC_Inventory> AC_Inventory;

	TSubclassOf<UUserWidget> InventorySlot;

	
	virtual void NativeConstruct() override;

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUpDate_CustomEvent);
	FUpDate_CustomEvent Update;

	UFUNCTION()
	void OnUpdate();
	
	UFUNCTION()
		void CalculateNewColumnAndRow();



};
