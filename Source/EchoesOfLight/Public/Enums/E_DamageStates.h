// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_Damage_State : uint8
{
	DoDamage UMETA(DisplayName = "Do Damage"),
	OnBlockDamage UMETA(DisplayName = "On Block Damage"),
	OnParry UMETA(DisplayName = "On Parry"),
	NoDamage UMETA(DisplayName = "No Damage"),
	None UMETA(DisplayName = "None")

};