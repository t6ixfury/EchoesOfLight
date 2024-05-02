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
enum class E_CharacterDamageStates : uint8
{
	Damaged UMETA(DisplayName = "Character has been damaged"),
	NoDamage UMETA(DisplayName = "Character has not recieved damage")
};

UENUM(BlueprintType)
enum class E_Damage_Response : uint8
{
	None UMETA(DisplayName = "None"),
	HitReaction UMETA(DisplayName = "Hit Reaction"),
	Stagger UMETA(DisplayName = "Stagger"),
	Stun UMETA(DisplayName = "Stun"),
	KnockBack UMETA(DisplayName = "KnockBack")

};

UENUM(BlueprintType)
enum class E_Damage_State : uint8
{
	DoDamage UMETA(DisplayName = "Do Damage"),
	OnBlockDamage UMETA(DisplayName = "On Block Damage"),
	OnParry UMETA(DisplayName = "On Parry"),
	NoDamage UMETA(DisplayName = "No Damage"),
	None UMETA(DisplayName = "None")

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

/*

ITEM ENUMS
*/

UENUM()
enum class EItemQuality : uint8
{
	Shoddy UMETA(DisplayName = "Shoddy"),
	Common UMETA(DisplayName = "Common"),
	Quality UMETA(DisplayName = "Quality"),
	Masterwork UMETA(DisplayName = "Masterwork"),
	GrandMaster UMETA(DisplayName = "GrandMaster")
};


UENUM()
enum class EItemType : uint8
{
	Amulet UMETA(DisplayName = "Amulet"),
	Weapon UMETA(DisplayName = "Weapon"),
	Netherband UMETA(DisplayName = "Netherband"),
	Spell UMETA(DisplayName = "Spell"),
	Consumable UMETA(DisplayName = "Consumable"),
	Quest UMETA(DisplayName = "Quest"),
	Mudane UMETA(DisplayName = "Mudane"),
	Powerup UMETA(DisplayName = "Powerup")
};


UENUM()
enum class ECharacterState : uint8
{
	Combat UMETA(DisplayName = "Combat"),
	NonCombat UMETA(DisplayName = "Non-Combat")
	
};

/*
END OF ITEM ENUMS
*/
