// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_DialogueGui.generated.h"

class UW_DialogueBox;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_DialogueGui : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidget))
		UW_DialogueBox* DialogueBox;
	
};
