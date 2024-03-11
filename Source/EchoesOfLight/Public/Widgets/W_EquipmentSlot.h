// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EquipmentSlot.generated.h"

class UImage;
class ABase_Sword;
class UItemBase;
class UDragItemVisual;

UENUM()
enum class EEquipmentType : uint8
{
	DualSwords UMETA(Displayname = "Dual Swords"),
	Amulet UMETA(Displayname = "Amulet"),
	NetherBand UMETA(Displayname = "Dual Swords")
};

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
		UImage* EquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Type")
		EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere)
		UItemBase* ItemReference;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
		TSubclassOf<UDragItemVisual> DragItemVisualClass;


	virtual void NativeConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;


	
};
