// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_StatBox.generated.h"


class UImage;
class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_StatBox : public UUserWidget
{
	GENERATED_BODY()
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* StatIconTexture;

	UPROPERTY(meta = (BindWidget))
		UProgressBar* StatProgressBar;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* CurrentStatValue;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MaximumStatValue;

	UPROPERTY(meta = (BindWidget))
		UImage* StatImage;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
public:
	// Updates the stat Text in the statbox
	void SetStatValues(int32 StartingStatValue, int32 CapStatValue);

	//Updates the percentage of the progress bar in the stat box
	void SetProgressBarPercentage(int32 Value, int32 MaxValue);

	//Set Icon image for the Stat box
	void SetStatImage();

	virtual void NativeConstruct() override;


};
