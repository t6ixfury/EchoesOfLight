// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_Damage_Type : uint8
{
	None UMETA(DisplayName = "None"),
	Melee UMETA(DisplayName = "Inventory"),
	Projectile UMETA(DisplayName = "Projectile"),
	Explosion UMETA(DisplayName = "Explosion"),
	Enviroment UMETA(DisplayName = "Enviroment")

};