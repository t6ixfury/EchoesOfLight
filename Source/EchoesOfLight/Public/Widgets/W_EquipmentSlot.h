// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_EquipmentSlot.generated.h"

class UImage;
class ABase_Sword;

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
		UImage* Equipment;

	UPROPERTY()
		EEquipmentType EquipmentType;

	UPROPERTY(EditAnywhere)
		ABase_Sword* WeaponRef;



	
};
