// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_PauseMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_PauseMenu : public UUserWidget
{
	GENERATED_BODY()
		
public:

	UPROPERTY(meta = (BindWidget))
		UButton* ResumeButton;

	UPROPERTY(meta = (BindWidget))
		UButton* SaveButton;

	UPROPERTY(meta = (BindWidget))
		UButton* QuitButton;


	virtual void NativeConstruct() override;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void SaveGame();

	UFUNCTION()
	void QuitGame();


	
};
