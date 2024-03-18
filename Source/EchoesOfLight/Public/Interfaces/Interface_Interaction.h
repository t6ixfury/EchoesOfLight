// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interface_Interaction.generated.h"

class AMainCharacter;

UENUM()
enum class  EInteractableType : uint8
{
	Pickup UMETA(DisplayName = "Pickup"),
	NonPlayerCharcter UMETA(DisplayName = "NonPlayerCharcter"),
	Device UMETA(DisplayName = "Device"),
	Toggle UMETA(DisplayName = "Toggle"),
	Container UMETA(DisplayName = "Container"),
	Villager UMETA(DisplayName = "Villager")

};




USTRUCT(BlueprintType)
struct FInteractableData
{
	GENERATED_USTRUCT_BODY()

		FInteractableData() :
		InteractableType(EInteractableType::Pickup),
		Name(FText::GetEmpty()),
		Action(FText::GetEmpty()),
		Quantity(0),
		InteractionDuration(0.0f)
		{


		};

	UPROPERTY(EditInstanceOnly)
	EInteractableType InteractableType;

	UPROPERTY(EditInstanceOnly)
	FText Name;

	UPROPERTY(EditInstanceOnly)
	FText Action;

	UPROPERTY(EditInstanceOnly)
	int32 Quantity;

	// used for any action you want with a time to activate.
	UPROPERTY(EditInstanceOnly)
	float InteractionDuration;




};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInterface_Interaction : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ECHOESOFLIGHT_API IInterface_Interaction
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	virtual void BeginFocus();

	virtual void EndFocus();

	virtual void BeginInteract();

	virtual void EndInteract();

	virtual void Interact(AMainCharacter* PlayerCharacter);

	FInteractableData InteractableData;
};
