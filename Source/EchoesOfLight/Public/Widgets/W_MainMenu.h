// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_MainMenu.generated.h"


class AMainCharacter;
/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_MainMenu : public UUserWidget
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:
	UPROPERTY()
		AMainCharacter* PlayerCharacter;

	
//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------
protected:

	virtual void NativeConstruct() override;

	virtual void NativeOnInitialized() override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
};
