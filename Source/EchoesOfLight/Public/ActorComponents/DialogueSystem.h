// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/Interface_Interaction.h"
#include "DialogueSystem.generated.h"



USTRUCT()
struct FDialogueData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FName Name;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	FText Dialoguetext;

	UPROPERTY(EditAnywhere, Category = "DialogueData")
	USoundBase* VoiceDoialogue;


	UPROPERTY(EditAnywhere, Category = "DialogueData")
	UAnimMontage* InteractionMontage;


};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UDialogueSystem : public UActorComponent, public IInterface_Interaction
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogueSystem();

	UPROPERTY()
	FDialogueData DialogueData;

	UPROPERTY(EditAnywhere, Category = "Dialogue | Data Tables")
	UDataTable* NpcDataTable;

	UPROPERTY(EditAnywhere, Category = "Dialogue | Data Tables")
	UDataTable* GenericNpcDataTable;

	AMainCharacter* MainCharacter;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginFocus() override;

	virtual void EndFocus() override;

	virtual void BeginInteract() override;

	virtual void EndInteract() override;

	virtual void Interact(AMainCharacter* PlayerCharacter) override;

	void RetrieveDialogueData();

		
};
