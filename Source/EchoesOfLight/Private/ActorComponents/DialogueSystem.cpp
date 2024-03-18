// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/DialogueSystem.h"



// Sets default values for this component's properties
UDialogueSystem::UDialogueSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogueSystem::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void UDialogueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogueSystem::RetrieveDialogueData()
{
	if (NpcDataTable && !VillagerDialogueID.IsEmpty())
	{
		//get the item info from the data table.
		const FDialogueData* DialogueDataRow = NpcDataTable->FindRow<FDialogueData>(VillagerName, VillagerDialogueID);

		if (DialogueDataRow)
		{
			DialogueData.Dialoguetext = DialogueDataRow->Dialoguetext;
			DialogueData.InteractionMontage = DialogueDataRow->InteractionMontage;
			DialogueData.Name = DialogueDataRow->Name;
			DialogueData.VoiceDoialogue = DialogueDataRow->VoiceDoialogue;

		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("no row data."))
		}
		
	}
}

void UDialogueSystem::SetDialogueSentencesArray(FString InputString)
{
	FRegexPattern SentencePattern(TEXT("([.!?])\\s+"));
	FRegexMatcher Matcher(SentencePattern, InputString);

	int32 PrevMatchEnd = 0;

	while (Matcher.FindNext())
	{
		int32 MatchEnd = Matcher.GetMatchEnding();
		FString Sentence = InputString.Mid(PrevMatchEnd, MatchEnd - PrevMatchEnd - 1).TrimStartAndEnd();
		if (!Sentence.IsEmpty())
		{
			DialogueSentences.Add(Sentence);
		}
		PrevMatchEnd = MatchEnd;
	}

	// Add the last sentence if there's any text left after the last match
	if (PrevMatchEnd < InputString.Len())
	{
		FString Sentence = InputString.Mid(PrevMatchEnd).TrimStartAndEnd();
		if (!Sentence.IsEmpty())
		{
			DialogueSentences.Add(Sentence);
		}
	}
	/*
	for (const FString& Sentence : DialogueSentences)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Sentence);
	}
	*/
}

