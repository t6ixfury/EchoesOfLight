// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Save/Master_SaveGame.h"
#include "Save_Currency.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API USave_Currency : public UMaster_SaveGame
{
	GENERATED_BODY()

public:


	UPROPERTY(VisibleAnywhere, Category = CurrencySave)
		float sCurrency;

	USave_Currency();
	
};
