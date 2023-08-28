// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_Global_Systems : uint8
{
	Inventory UMETA(DisplayName = "Inventory"),
	Experience UMETA(DisplayName = "Experience"),
	Currency UMETA(DisplayName = "Currency")
	
};

UENUM(BlueprintType)
enum class E_Damage_Type : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Inventory"),
	Projectile UMETA(DisplayName = "Projectile"),
	Explosion UMETA(DisplayName = "Explosion"),
	Enviroment UMETA(DisplayName = "Enviroment")
	
};

UENUM(BlueprintType)
enum class E_UnLock_Type : uint8
{
	HoldButton UMETA(DisplayName = "HoldButton"),
	KeyUnlock UMETA(DisplayName = "keyUnlock")
	
};

UENUM(BlueprintType)
enum class E_Task_Type : uint8
{
	Guardians UMETA(DisplayName = "Guardians"),
	Chest UMETA(DisplayName = "Chest"),
	Item UMETA(DisplayName = "Item"),
	Overlap UMETA(DisplayName = "Overlap")

};

UENUM(BlueprintType)
enum class E_Item_Type : uint8
{
	Food UMETA(DisplayName = "Food"),
	Experience UMETA(DisplayName = "Experience"),
	Weapon UMETA(DisplayName = "Weapon"),
	Miscellanous UMETA(DisplayName = "Miscellanous")

};

