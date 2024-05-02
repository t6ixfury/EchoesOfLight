// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_DeathMenu.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_DeathMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(Editanywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* RestartLevel;

	UPROPERTY(Editanywhere, BlueprintReadWrite, meta = (BindWidget))
		UButton* QuitLevel;

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
		void Restart();

	UFUNCTION(BlueprintCallable)
		void QuitGame();
};
