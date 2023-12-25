// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"

#include "W_InventorySlot.generated.h"

class AItem;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_InventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UImage* InventorySlotImage;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Item Reference")
		AItem* ItemInslot;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		bool bHasItem = false;

	UPROPERTY(VisibleAnywhere)
		UTexture2D* Texture;


	
	



public:

	virtual void NativeConstruct() override;

	void SetItemIconImage(UTexture2D* TextureToSet);

	void setItemInSlot(AItem* ItemToSet);





};
