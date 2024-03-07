// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Widgets/W_StatBox.h"

//engine
#include "Components/Image.h"        
#include "Components/ProgressBar.h"  
#include "Components/TextBlock.h"   

void UW_StatBox::SetStatValues(int32 StartingStatValue, int32 CapStatValue)
{
	CurrentStatValue->SetText(FText::AsNumber(StartingStatValue));
	MaximumStatValue->SetText(FText::AsNumber(CapStatValue));
}

void UW_StatBox::SetStatImage()
{
	if (StatIconTexture)
	{
		StatImage->SetBrushFromTexture(StatIconTexture);
	}
}

void UW_StatBox::NativeConstruct()
{
	Super::NativeConstruct();

	SetStatImage();
}
