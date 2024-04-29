// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_ItemMenu.generated.h"


class UButton;
class UTextBlock;
class UItemBase;



/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_ItemMenu : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
		UTextBlock* MenuTitle;

	UPROPERTY(meta = (BindWidget))
		UButton* UseButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* UseButtonText;

	UPROPERTY(meta = (BindWidget))
		UButton* EquipButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* EquipButtonText;

	UPROPERTY(meta = (BindWidget))
		UButton* DeleteButton;

	UPROPERTY(meta = (BindWidget))
		UTextBlock* DeleteButtonText;

	UPROPERTY()
		UItemBase* item;


	virtual void NativeOnInitialized() override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;


	UFUNCTION()
	void UseItem();

	UFUNCTION()
	void Equip();

	UFUNCTION()
	void Delete();


	
};
