// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interface_Damagable.h"
#include "Blueprint/UserWidget.h"
#include "W_MainGUI.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_MainGUI : public UUserWidget
{
	GENERATED_BODY()




		
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:

	UPROPERTY(meta = (BindWidget))
		class UProgressBar* HealthBar;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:
	void SetHealthBarPercentage(float newHealth);

	
};
