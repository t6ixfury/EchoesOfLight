// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/EnemyHealthBar.h"

//engine
#include "Components/ProgressBar.h"

void UEnemyHealthBar::SetHealthBarPercentage(float newHealth)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(newHealth);
	}
}
