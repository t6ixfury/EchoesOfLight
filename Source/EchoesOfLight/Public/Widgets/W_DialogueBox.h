// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "W_DialogueBox.generated.h"

class UTextBlock;
class UMultiLineEditableTextBox;

/**
 * 
 */
UCLASS()
class ECHOESOFLIGHT_API UW_DialogueBox : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(VisibleAnywhere, Category = "Dialogue Box", meta = (BindWidget))
	UTextBlock* CharacterName;
	
	UPROPERTY(VisibleAnywhere, Category = "Dialogue Box", meta = (BindWidget))
		UTextBlock* DialogueText;

	bool bHasDialogueText = true;

	TArray<FString> sentences; 

	int32 SentencesIndex = 0;

	void SetDialogueText(FString message);

	void SetName(FName name);

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	void GoToTheNextDialogueSentence();


};

