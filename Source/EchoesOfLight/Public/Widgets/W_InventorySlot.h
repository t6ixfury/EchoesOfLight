// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"

#include "W_InventorySlot.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
		FDataTableRowHandle SlotItem;

	UFUNCTION(BlueprintCallable, Category = "Initialization")
		void SetItem(const FDataTableRowHandle& InSlotItem);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* Texture;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* InventorySlotImage;

	class UBFL_Utility* Utility;

public:

	virtual void NativeConstruct() override;




};
