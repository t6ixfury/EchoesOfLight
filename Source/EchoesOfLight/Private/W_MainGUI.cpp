// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "W_MainGUI.h"

//engine
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UW_MainGUI::SetHealthBarPercentage(float newHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(newHealth);
	}
}

void UW_MainGUI::SetStaminaBarPercetage(float newStamina)
{
	if (StaminaBar)
	{
		StaminaBar->SetPercent(newStamina);
	}
}

void UW_MainGUI::SetExperienceBarPercentage(float newExperience)
{
	if (ExperienceBar)
	{
		ExperienceBar->SetPercent(newExperience);
	}
}

void UW_MainGUI::SetLevelText(FText NewLevel)
{
	if (LevelText)
	{
		LevelText->SetText(NewLevel);
	}
}

