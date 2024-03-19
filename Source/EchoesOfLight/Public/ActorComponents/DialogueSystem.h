// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogueSystem.generated.h"

class AMainCharacter;

USTRUCT()
struct FDialogueData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FString Dialoguetext;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	USoundBase* VoiceDoialogue;


	UPROPERTY(EditAnywhere, Category = "DialogueData")
	UAnimMontage* InteractionMontage;


};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UDialogueSystem : public UActorComponent
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------


public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Villager Information")
		FName VillagerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Villager Information")
		FString VillagerDialogueID;

	UPROPERTY()
	FDialogueData DialogueData;

	UPROPERTY()
		TArray<FString> DialogueSentences;

	UPROPERTY(EditAnywhere, Category = "Dialogue | Data Tables")
	UDataTable* NpcDataTable;

	UPROPERTY(EditAnywhere, Category = "Dialogue | Data Tables")
	UDataTable* GenericNpcDataTable;

	AMainCharacter* MainCharacter;

	bool bIsTalking = false;



//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:

	// Sets default values for this component's properties
	UDialogueSystem();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void RetrieveDialogueData();

	void SetDialogueSentencesArray(FString InputString);

		
};
