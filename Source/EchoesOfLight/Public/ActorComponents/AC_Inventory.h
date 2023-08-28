// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Inventory.generated.h"

class UW_Inventory;
struct FDataTableRowHandle;
class AMainCharacter;
class APlayerController;
class USave_Inventory;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UAC_Inventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAC_Inventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void AddItems(TArray<FDataTableRowHandle> items);

	UFUNCTION(BlueprintCallable)
		void UpdateInventory();

	UFUNCTION(BlueprintCallable)
		void SaveInventory();

	UFUNCTION(BlueprintCallable)
		void LoadInventory();

public:

	UPROPERTY(BlueprintReadOnly)
		TArray<FDataTableRowHandle> Inventory;

	UPROPERTY(BlueprintReadOnly)
		UW_Inventory* InventoryWidget;

	UPROPERTY(BlueprintReadOnly)
		AMainCharacter* MainCharacter;

	UPROPERTY(BlueprintReadOnly)
		APlayerController* CharacterController;

	UPROPERTY(BlueprintReadOnly)
		FString InventorySlot;

	UPROPERTY(BlueprintReadOnly)
		USave_Inventory* SaveGame;

	/*
	EVENTS
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FToggleInventory_CustomEvent);
	FToggleInventory_CustomEvent ToggleInventoryEvent;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInitializePlayer_CustomEvent);
	FInitializePlayer_CustomEvent InitializePlayerEvent;

	//

	UFUNCTION()
		void IntializePlayerEvent(UW_Inventory* InventoryToSet);

	UFUNCTION(BlueprintCallable)
		void ToggleInventory();




		
};
