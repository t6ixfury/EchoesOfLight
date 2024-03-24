// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_Alert.h"
#include "Components/TextBlock.h"


void UW_Alert::SetAlertTitleText(FText title)
{
	AlertTitleText->SetText(title);
}

void UW_Alert::SetAlertMessageText(FText message)
{
	AlertMessageText->SetText(message);
}
