// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/W_DialogueGui.h"
#include "Widgets/W_DialogueBox.h"

FReply UW_DialogueGui::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("on keydown"))
	if (InKeyEvent.GetKey() == EKeys::F)
	{
		DialogueBox->GoToTheNextDialogueSentence();

		return FReply::Handled();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}
