// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/Interface_Damagable.h"
#include "Blueprint/UserWidget.h"
#include "W_MainGUI.generated.h"

/**
 * 
 */

class UProgressBar;
class UTextBlock;
UCLASS()
class ECHOESOFLIGHT_API UW_MainGUI : public UUserWidget
{
	GENERATED_BODY()




		
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:

	UPROPERTY(meta = (BindWidget))
		UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StaminaBar;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* ExperienceBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* LevelText;



//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:
	void SetHealthBarPercentage(float newHealth);
	void SetStaminaBarPercetage(float newStamina);
	void SetExperienceBarPercentage(float newExperience);
	void SetLevelText(FText NewLevel);

	
};
