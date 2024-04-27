// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Alert.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_Alert : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Alert Widget | Data")
		UTextBlock* AlertTitleText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Alert Widget | Data")
		UTextBlock* AlertMessageText;


	UPROPERTY(Transient, BlueprintReadOnly, meta = (BindWidgetAnim))
		UWidgetAnimation* FadeIn;

	void SetAlertTitleText(FText title);

	void SetAlertMessageText(FText message);

	float PlayAlertAnimation();

	
};
