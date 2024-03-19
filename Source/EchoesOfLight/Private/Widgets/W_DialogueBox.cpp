// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_DialogueBox.h"
#include "Components/TextBlock.h"
#include "Components/MultiLineEditableTextBox.h"


void UW_DialogueBox::SetDialogueText(FString message)
{
	DialogueText->SetText(FText::FromString(message));
}

void UW_DialogueBox::SetName(FName name)
{
	CharacterName->SetText(FText::FromName(name));
}

FReply UW_DialogueBox::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UW_DialogueBox::GoToTheNextDialogueSentence()
{
	if (sentences.Num() > SentencesIndex + 1 )
	{
		SentencesIndex += 1;
		SetDialogueText(sentences[SentencesIndex]);
		UE_LOG(LogTemp, Warning, TEXT("nextdialogue"))

	}
	if ((sentences.Num() - 1 == SentencesIndex + 1) && (sentences.Num() == SentencesIndex + 2))
	{
		bHasDialogueText = false;
		SentencesIndex = 0;
		sentences.Empty();
	}
}


