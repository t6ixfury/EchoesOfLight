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

	// ...
	
}


// Called every frame
void UDialogueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogueSystem::BeginFocus()
{
}

void UDialogueSystem::EndFocus()
{
}

void UDialogueSystem::BeginInteract()
{
}

void UDialogueSystem::EndInteract()
{
}

void UDialogueSystem::Interact(AMainCharacter* PlayerCharacter)
{
}

void UDialogueSystem::RetrieveDialogueData()
{
}

