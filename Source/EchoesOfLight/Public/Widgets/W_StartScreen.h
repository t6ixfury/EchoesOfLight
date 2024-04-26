// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_StartScreen.generated.h"



class UButton;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_StartScreen : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(meta = (BindWidget))
		UButton* StartGame;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitGame;

	const FName FirstLevel = TEXT("Town_0_No_Foliage_Start");

	FName LevelBeingLoaded;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void Start();

	UFUNCTION()
	void Quit();



private:
	// Timer handle for the repeating function
	UPROPERTY()
	FTimerHandle loadWaitTimerHandle;


};
