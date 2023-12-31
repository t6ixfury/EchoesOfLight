// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_Interact.generated.h"

class AMainCharacter;
struct FInteractableData;
class UTextBlock;
class UProgressBar;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_Interact : public UUserWidget
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:
	UPROPERTY(VisibleAnywhere, Category = "Interaction Widget | Player Reference")
		AMainCharacter* PlayerCharacter;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

	void UpdateWidget(const FInteractableData* InteractionData) const;

protected:
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	UTextBlock* NameText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	UTextBlock* ActionText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	UTextBlock* QuantityText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	UTextBlock* KeyPressText;

	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	UProgressBar* InteractionProgressBar;

	//possible problem because I dont think there is a wigdet to bind to. 
	UPROPERTY(VisibleAnywhere, meta = (BindWidget), Category = "Interaction Widget | Data")
	float CurrentInteractionDuration;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintCallable, meta = (BindWidget), Category = "Interaction Widget | Data")
	float UpdateInteractionProgressBar();

};
