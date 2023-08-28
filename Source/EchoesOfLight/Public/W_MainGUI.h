// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainGUI.generated.h"

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_MainGUI : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* HealthBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UW_Inventory* Inventory;


	
	
};
