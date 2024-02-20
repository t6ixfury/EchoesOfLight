// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "W_MainGUI.h"

//engine
#include "Components/ProgressBar.h"


void UW_MainGUI::SetHealthBarPercentage(float newHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(newHealth);
	}
}
