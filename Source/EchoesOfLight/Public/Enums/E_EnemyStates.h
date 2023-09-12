// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class E_EnemyDamageStates : uint8
{
	ApplyDamage UMETA(DisplayName = "Character has been damaged"),
	DoNotApplyDamage UMETA(DisplayName = "Character has not recieved damage")
};

UENUM(BlueprintType)
enum class E_EnemyAI_Sense : uint8
{
	None UMETA(DisplayName = "None"),
	Sight UMETA(DisplayName = "Sight"),
	Hearing UMETA(DisplayName = "Hearing"),
	Damage UMETA(DisplayName = "Damage"),
	Touch UMETA(DisplayName = "Touch"),
	Prediction UMETA(DisplayName = "Prediction"),
	Team UMETA(DisplayName = "Team")
};

UENUM(BlueprintType)
enum class E_EnemyAI_State : uint8
{
	Passive UMETA(DisplayName = "Passive"),
	Attacking UMETA(DisplayName = "Attacking"),
	Frozen UMETA(DisplayName = "Frozen"),
	Investigating UMETA(DisplayName = "Investigating"),
	Death UMETA(DisplayName = "Death")
};

UENUM(BlueprintType)
enum class E_Enemy_type : uint8
{
	Undead UMETA(DisplayName = "Undead"),
	Beast UMETA(DisplayName = "Attacking"),
	Arcane UMETA(DisplayName = "Frozen")
};
