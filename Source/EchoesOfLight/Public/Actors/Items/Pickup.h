// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "Pickup.generated.h"

class UItemBase;
class UDataTable;
class FName;

UCLASS()
class ECHOESOFLIGHT_API APickup : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()
//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:	
	UPROPERTY(EditAnywhere, Category = "Pickup | Item Initialization")
		int32 ItemQuantity;

protected:

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Components")
	UStaticMeshComponent* PickupMesh;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Initialization")
	UDataTable* ItemDataTable;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Initialization")
	FName DesiredItemId;

	UPROPERTY(EditAnywhere, Category = "Pickup | Item Reference")
	UItemBase* ItemReference;

	UPROPERTY(VisibleAnywhere, Category = "Pickup | Interaction")
	FInteractableData InstanceInteractableData;




//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:	

	// Sets default values for this actor's properties
	APickup();


	void InitializePickup(const int32 InQuantity);

	void InitializeDrop(UItemBase* ItemToDrop, const int32 InQuantity);

	FORCEINLINE UItemBase* GetItemData() { return ItemReference; };


	/*Interaction Interface Functions*/

	virtual void BeginFocus() override; 
	virtual void EndFocus() override;
	virtual void Interact(AMainCharacter* PlayerCharacter) override;


	/*END*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void TakePickup(const AMainCharacter* Taker);
	//Updates the interact widget with the data of the item you are looking at.
	void UpdateInteractableData();


// Use this to only be called when editing in the editor and not shipped code.
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif 
};
