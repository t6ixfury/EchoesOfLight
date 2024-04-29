// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EquipmentSlot.generated.h"

class UImage;
class ABase_Sword;
class UItemBase;
class UDragItemVisual;
enum class EItemType:uint8;
class UInventoryToolTip;



UENUM()
enum class EEquipmentType : uint8
{
	DualSwords UMETA(Displayname = "Dual Swords"),
	Amulet UMETA(Displayname = "Amulet"),
	NetherBand UMETA(Displayname = "Dual Swords")
};


DECLARE_MULTICAST_DELEGATE(FWeaponEquippedDelegate);
DECLARE_MULTICAST_DELEGATE(FAmuletEquippedDelegate);
DECLARE_MULTICAST_DELEGATE(FNetherbandEquippedDelegate);

UCLASS()
class ECHOESOFLIGHT_API UW_EquipmentSlot : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
		UImage* EquipmentIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Equipment Type")
		EItemType EquipmentType;

	UPROPERTY(EditAnywhere, Category = "Item")
		UDataTable* WeaponDataTable;

	UPROPERTY(EditAnywhere, Category = "Item")
		UDataTable* AmuletDataTable;

	UPROPERTY(EditAnywhere, Category = "Item")
		UDataTable* NetherBandDataTable;

	UPROPERTY(EditAnywhere)
		UItemBase* ItemReference;
	
	UPROPERTY()
	FName SlotItemId;

	UPROPERTY(EditDefaultsOnly, Category = "Inventory Slot")
		TSubclassOf<UDragItemVisual> DragItemVisualClass;


	UPROPERTY(EditAnywhere, Category = "Equipment Slot")
		UInventoryToolTip* ToolTip;

	FWeaponEquippedDelegate WeaponChange;

	FAmuletEquippedDelegate AmuletChange;

	FNetherbandEquippedDelegate NetherBandChange;


	virtual void NativeConstruct() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnInitialized() override;

	//Handles Logic for when an equipment item is added to it perspective spot and calls the correct delegate.
	EItemType EventItemEquipped(EItemType EquipmentTypeToBeHandled, UItemBase* ItemRef);

	void SetIconImage();

	void CreateItem(UDataTable* table, FName DesiredItemId);

	UItemBase* GetItemReference();





	
};
