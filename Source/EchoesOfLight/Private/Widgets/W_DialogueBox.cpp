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


