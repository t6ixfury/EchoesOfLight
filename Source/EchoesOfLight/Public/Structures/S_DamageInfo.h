// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/Enums.h"
#include "S_DamageInfo.generated.h"


USTRUCT(BlueprintType)
struct ECHOESOFLIGHT_API FS_DamageInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 AttackPower = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MagicPower = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CriticalHitRate = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 AtttackSpeed = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 MaxStatValue = 99;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 1;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Experience = 0;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		E_Damage_Type DamageType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		E_Damage_Response DamageResponse;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShouldDamageInvincible = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCanBeBlocked = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCanBeParried = false;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bShouldForceInterrupt = false;

};
