// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Inventory.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdated);


class UItemBase;


//This will be used to as result for how many items are picked up.
UENUM()
enum class EItemAddResult : uint8
{
	IAR_NoItemAdded UMETA(DisplayName = "No Item Added"),
	IAR_PartialAmountItemAdded UMETA(DisplayName = "Partial Item Added"),
	IAR_AllItemAdded UMETA(DisplayName = "All Item Added")
};

// This will store the result of the item pick up operation.
USTRUCT(BlueprintType)
struct FItemAddResult
{
	GENERATED_BODY()

	FItemAddResult() : ActualAmountAdded(0), OperationResult(EItemAddResult::IAR_NoItemAdded), ResultMessage(FText::GetEmpty()) {};

	//This will represent the Actual amount of items you added to your inventory.
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	int32 ActualAmountAdded;

	//Represents how many items were picked up.
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	EItemAddResult OperationResult;

	//Used to give user feedback in cases such as the inventory is full.
	UPROPERTY(BlueprintReadOnly, Category = "Item Add Result")
	FText ResultMessage;

	//Call This Function to set the FItemAddedResult variable if no item was added to the inventory.
	static FItemAddResult AddedNone(const FText& ErrorText)
	{
		FItemAddResult AddedNoneResult;
		AddedNoneResult.ActualAmountAdded = 0;
		AddedNoneResult.OperationResult = EItemAddResult::IAR_NoItemAdded;
		AddedNoneResult.ResultMessage = ErrorText;

		return AddedNoneResult;
	};
	//Call This Function to set the FItemAddedResult variable if only a partial amount of the item was added to the inventory.
	static FItemAddResult AddedPartial(const int32 PartialAmountAdded, const FText& ErrorText)
	{
		FItemAddResult AddedPartialResult;
		AddedPartialResult.ActualAmountAdded = PartialAmountAdded;
		AddedPartialResult.OperationResult = EItemAddResult::IAR_PartialAmountItemAdded;
		AddedPartialResult.ResultMessage = ErrorText;

		return AddedPartialResult;
	};
	//Call This Function to set the FItemAddedResult variable if all items was added to the inventory.
	static FItemAddResult AddedAll(const int32 AmountAdded, const FText& Message)
	{
		FItemAddResult AddedAllResult;
		AddedAllResult.ActualAmountAdded = AmountAdded;
		AddedAllResult.OperationResult = EItemAddResult::IAR_AllItemAdded;
		AddedAllResult.ResultMessage = Message;

		return AddedAllResult;
	};




};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UAC_Inventory : public UActorComponent
{
	GENERATED_BODY()


//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:	

	FOnInventoryUpdated OnInventoryUpdated;

protected:

	//Represents the total weight the player is currently carring.
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	float InventoryTotalWeight;

	// Represents the total number of slots in the inventory.
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	int32 InventorySlotsCapacity;

	//Represents the total Weight a player can carry.
	UPROPERTY(EditInstanceOnly, Category = "Inventory")
	float InventoryWeightCapacity;

	//An array of all the items in the inventory.
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<TObjectPtr<UItemBase>> InventoryContents;


//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:	
	// Sets default values for this component's properties.
	UAC_Inventory();

	//Handles logic on wether an item is added or not. Also how much of the item is added to the inventory and returns the info in a struct.
	UFUNCTION(Category = "Inventory")
	FItemAddResult HandleAddItem(UItemBase* InputItem);

	UFUNCTION(Category = "Inventory")
		UItemBase* FindItembyName(FName ItemName);

	// Check to see if the Item of same type being added is all ready in the inventory.
	UFUNCTION(Category = "Inventory")
	UItemBase* FindMatchingItem(UItemBase* ItemIn) const;

	//Searches (Fill out later)
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextItemByID(UItemBase* ItemIn) const;

	//Searches For the passed in item in the inventory. If found and the item stack is not full, returns the item.
	UFUNCTION(Category = "Inventory")
	UItemBase* FindNextPartialStack(UItemBase* ItemIn) const;

	//This will move an Item from the Inventory.
	UFUNCTION(Category = "Inventory")
	void RemoveSingleInstanceOfItem(UItemBase* ItemToRemove);

	//This will move a desired amount of Items from the Inventory.
	UFUNCTION(Category = "Inventory")
	int32 RemoveAmountOfItem(UItemBase* ItemToRemove, const int32 DesiredAmount);

	//This will split an item stack by a specified amount.
	UFUNCTION(Category = "Inventory")
	void SplitExistingStack(UItemBase* Item, const int32 AmountToSplit);


	/*GETTER FUNCTIONS*/

	// This returns the current total weight carried by the player.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetInventoryTotalWeight() const { return InventoryTotalWeight; };

	// This returns the total possible weight that can be carried by the player.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE float GetWeightCapacity() const { return InventoryWeightCapacity; };

	//Returns the total number of slots for the inventory.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE int32 GetSlotsCapacity() const { return InventorySlotsCapacity; };

	// Returns a TArray of items in the Inventory.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE TArray<UItemBase*> GetInventoryContents() const { return InventoryContents; };

	/*SETTER FUNCTIONS*/

	//This set the number of slots possible in the inventory.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetSlotsCapacity(const int32 NewSlotsCapacity) { InventorySlotsCapacity = NewSlotsCapacity; };

	//This sets the total weight capacity for the inventory.
	UFUNCTION(Category = "Inventory")
	FORCEINLINE void SetWeightCapacity(const int32 NewWeightCapacity) { InventoryWeightCapacity = NewWeightCapacity; };

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Handles the checks neccessary to add the non-stackable item to the inventory
	FItemAddResult HandleNonStackableItems(UItemBase* Item);

	// Handles the checks neccessary to add the stackable item to the inventory
	int32 HandleStackableItems(UItemBase* Item, int32 RequestedAmount);

	//returns How many items can be added with the players current weight
	int32 CalculateWeightAddAmount(UItemBase* Item, int32 RequestedAmount);

	//Calculates how many more items can fit in the stack.
	int32 CalculateNumberForFullStack(UItemBase* StackableItem, int32 IntialRequestedAmount);

	//Adds Item to player inventory
	void AddNewItem(UItemBase* Item, const int32 ItemAmountToAdd);





		
};
