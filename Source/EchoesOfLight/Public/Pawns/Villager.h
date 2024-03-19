// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interface_Interaction.h"
#include "Villager.generated.h"

class UDialogueSystem;
class ADialogueCamera;
class AMainCharcter;


UCLASS()
class ECHOESOFLIGHT_API AVillager : public ACharacter, public IInterface_Interaction
{
	GENERATED_BODY()


//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
		UDialogueSystem* Dialogue;

	AMainCharacter* CharacterRef;

	FRotator CharacterRotation;

	UPROPERTY(EditAnywhere, Category = "Timeline")
	float RotationSpeed=1;


	ADialogueCamera* DialogueCamera;
	bool bisDoneRotating = false;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------


public:

	// Sets default values for this pawn's properties
	AVillager();

	virtual void BeginFocus() override;

	virtual void EndFocus() override;

	virtual void BeginInteract() override;

	virtual void EndInteract() override;

	virtual void Interact(AMainCharacter* PlayerCharacter) override;

	void SetInteractableData();

	void SetVillagerRotation(float DeltaTime);

	void SetDialogueCameraView(AMainCharacter* Character);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


};
