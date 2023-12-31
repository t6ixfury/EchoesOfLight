// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/AC_Inventory.h"
#include "Actors/Items/ItemBase.h"

// Sets default values for this component's properties
UAC_Inventory::UAC_Inventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


}

// Called when the game starts
void UAC_Inventory::BeginPlay()
{
	Super::BeginPlay();
	
	
}


// Called every frame
void UAC_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

UItemBase* UAC_Inventory::FindMatchingItem(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		//check to see if the passed in Item in the Inventory and if it is return the passed in Item
		if (InventoryContents.Contains(ItemIn))
		{
			return ItemIn;
		}
	}

	return nullptr;
}

UItemBase* UAC_Inventory::FindNextItemByID(UItemBase* ItemIn) const
{
	if (ItemIn)
	{
		//Double pointer.
		// this creates a pointer (TArray<TObjectPtr<UItemBase>>) which then creates another pointer (Result) of the type of the elements contained in the array.
		//then you find by key on the inventory using the overload that we set in itembase and set result to that item if found..
		if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result = InventoryContents.FindByKey(ItemIn))
		{
			//then we dereference to first pointer to get the proper location in the array by this getting this pointer (TArray<TObjectPtr<UItemBase>>)
			return *Result;
		}
	}

	return nullptr;
}


UItemBase* UAC_Inventory::FindNextPartialStack(UItemBase* ItemIn) const
{
	// uses lammda function to find a partial stack. Predicate is just a fancy word to describe a condition.
	if (const TArray<TObjectPtr<UItemBase>>::ElementType* Result =
		InventoryContents.FindByPredicate([&ItemIn](const UItemBase* InventoryItem)
			{
				return InventoryItem->ID == ItemIn->ID && !InventoryItem->IsFullItemStack();
			}
		))
	{
		return *Result;
	}

	return nullptr;
}

int32 UAC_Inventory::CalculateWeightAddAmount(UItemBase* Item, int32 RequestedAmount)
{
	//Caculates the max number of items you can add for the specific item
	const int32 WeightMaxAddAmount = FMath::FloorToInt((GetWeightCapacity() - InventoryTotalWeight) / Item->GetItemSingleWeight());

	//checks to see if the requested amount can be added and if not return the max add amount.
	if (WeightMaxAddAmount >= RequestedAmount)
	{
		return RequestedAmount;
	}

	return WeightMaxAddAmount;
}

int32 UAC_Inventory::CalculateNumberForFullStack(UItemBase* StackableItem, int32 IntialRequestedAmount)
{
	//calculates how many more items can fit in the stack
	const int32 AddAmountToMakeFullStack = StackableItem->ItemNumericaData.MaxStackSize - StackableItem->Quantity;

	//returns the lower of either the Intial requested amout or the add amount
	return FMath::Min(IntialRequestedAmount, AddAmountToMakeFullStack);
}

void UAC_Inventory::RemoveSingleInstanceOfItem(UItemBase* ItemToRemove)
{
	//remove item from the inventory array
	InventoryContents.RemoveSingle(ItemToRemove);

	OnInventoryUpdated.Broadcast();
}

int32 UAC_Inventory::RemoveAmountOfItem(UItemBase* ItemToRemove, const int32 DesiredAmount)
{
	const int32 ActualAmountToRemove = FMath::Min(DesiredAmount, ItemToRemove->Quantity);

	ItemToRemove->SetQuantity(ActualAmountToRemove);


	InventoryTotalWeight -= ActualAmountToRemove * ItemToRemove->GetItemSingleWeight();

	if (!ItemToRemove->ItemNumericaData.bisStackable && DesiredAmount == 1)
	{
		RemoveSingleInstanceOfItem(ItemToRemove);
	}

	OnInventoryUpdated.Broadcast();

	return ActualAmountToRemove;
}

void UAC_Inventory::SplitExistingStack(UItemBase* Item, const int32 AmountToSplit)
{
	//if one more Item will not overflow inventory
	if (!(InventoryContents.Num() + 1 > InventorySlotsCapacity))
	{
		RemoveAmountOfItem(Item, AmountToSplit);
		AddNewItem(Item, AmountToSplit);

	}
}


FItemAddResult UAC_Inventory::HandleNonStackableItems(UItemBase* Item)
{
	//check if in the input item has valid weight.
	if (FMath::IsNearlyZero(Item->GetItemSingleWeight()) || Item->GetItemSingleWeight() < 0 )
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could Not add {0} to the Inventory. Item has invalid weight value."), Item->ItemTextData.Name));
	}

	// Will the item weight overflow the capacity.
	if (InventoryTotalWeight + Item->GetItemSingleWeight() > GetWeightCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could Not add {0} to the Inventory. Item would overflow weight limit."), Item->ItemTextData.Name));
	}

	//adding one more item would overflow slot capacity.
	if (InventoryContents.Num() + 1 > GetSlotsCapacity())
	{
		return FItemAddResult::AddedNone(FText::Format(FText::FromString("Could Not add {0} to the Inventory. All inventory slots are full."), Item->ItemTextData.Name));
	}

	AddNewItem(Item, 1);

	return FItemAddResult::AddedAll( 1, 
		FText::Format(FText::FromString("Successfully added {0} to the Inventory. All inventory slots are full."), Item->ItemTextData.Name));
}

int32 UAC_Inventory::HandleStackableItems(UItemBase* Item, int32 RequestedAmount)
{
	if (RequestedAmount <= 0 || FMath::IsNearlyZero(Item->GetItemStackWeight()))
	{
		//invalid item data
		return 0;
	}

	int32 AmountToDistrubite = RequestedAmount;

	//check if the input item already exist in the inventory and is not a full stack;
	UItemBase* ExistingItemStack = FindNextPartialStack(Item);

	//distribute item stack over existing stacks.
	while (ExistingItemStack)
	{
		//calculate how many of the existing item would be needed to make the next full stack
		const int32 AmountToMakeFullStack = CalculateNumberForFullStack(ExistingItemStack, AmountToDistrubite);

		//calculate how many of the AmountToMakeFullstack can acutally be carried based on weight capacity
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(ExistingItemStack, AmountToMakeFullStack);
		
		//as long as the remaining amount of the item does not overflow weight capacity
		if (WeightLimitAddAmount > 0)
		{
			//adjust the existing Items stack quantity and inventory total weight
			ExistingItemStack->SetQuantity(ExistingItemStack->Quantity + WeightLimitAddAmount);
			InventoryTotalWeight += (ExistingItemStack->GetItemSingleWeight() * WeightLimitAddAmount);

			//adjust the count to be distributed
			AmountToDistrubite -= WeightLimitAddAmount;

			Item->SetQuantity(AmountToDistrubite);

			//if max weight capacity is reached, no need tor run the loop again.
			if (InventoryTotalWeight >= InventoryWeightCapacity)
			{
				OnInventoryUpdated.Broadcast();

				return RequestedAmount - AmountToDistrubite;
			}
		}
		else if (WeightLimitAddAmount <= 0)
		{
			if (AmountToDistrubite != RequestedAmount)
			{
				//this block will be reached if distributing an item across multiple stacks and the weight limit is hit during that process
				OnInventoryUpdated.Broadcast();

				return RequestedAmount - AmountToDistrubite;
			}
			// if the amount left is = to requestes amount no items left to distrubite.
			return 0;

		}

		if (AmountToDistrubite <= 0)
		{
			// all of the input item was distributed across existing stacks.
			OnInventoryUpdated.Broadcast();
			return RequestedAmount;
		}

		//check if there is still another valid partial stack of the input item.
		ExistingItemStack = FindNextPartialStack(Item);
	}

	//no more partial stacks found, check if a new stack can be added
	if (InventoryContents.Num() + 1 <= InventorySlotsCapacity)
	{
		//attempt to add as many from the remainin item quantity that can fit inventory weight capacity.
		const int32 WeightLimitAddAmount = CalculateWeightAddAmount(Item, AmountToDistrubite);

		if (WeightLimitAddAmount > 0)
		{
			//if there is still more items to distribute, but weight limit has been reached.
			if (WeightLimitAddAmount < AmountToDistrubite)
			{
				//adjust the input item and add a new stack with as many as can be held
				AmountToDistrubite -= WeightLimitAddAmount;
				Item->SetQuantity(AmountToDistrubite);

				//create a copy since only a partial stack is being add
				AddNewItem(Item->CreateItemCopy(), WeightLimitAddAmount);

				return RequestedAmount - AmountToDistrubite;
			}

			//otherwise, the full remainder of the stack can be added.
			AddNewItem(Item, WeightLimitAddAmount);
			return RequestedAmount;
		}
	}

	OnInventoryUpdated.Broadcast();
	return RequestedAmount - AmountToDistrubite;
}

FItemAddResult UAC_Inventory::HandleAddItem(UItemBase* InputItem)
{
	if (GetOwner())
	{
		const int32 IntialRequestAddAmount = InputItem->Quantity;
		//Handle non-Stackable Items
		if (!InputItem->ItemNumericaData.bisStackable)
		{
			return HandleNonStackableItems(InputItem);
		}

		//Handle Stackable
		const int32 StackableAmountAdded = HandleStackableItems(InputItem, IntialRequestAddAmount);

		if (StackableAmountAdded == IntialRequestAddAmount)
		{
			return FItemAddResult::AddedAll(IntialRequestAddAmount, FText::Format(FText::FromString("Successfully added {0} {1} to the inventory."),
				IntialRequestAddAmount, InputItem->ItemTextData.Name));
		}
		if (StackableAmountAdded < IntialRequestAddAmount && StackableAmountAdded > 0)
		{
			return FItemAddResult::AddedPartial(IntialRequestAddAmount, FText::Format(FText::FromString("Partial amount of {0} added to the inventory. Number Added = {1}"),
				InputItem->ItemTextData.Name, StackableAmountAdded));
		}
		if (StackableAmountAdded <= 0)
		{
			return FItemAddResult::AddedNone(FText::Format(FText::FromString("Couldn't add {0} to the inventory. No remaining inventory slots, or invalid item."),
				 InputItem->ItemTextData.Name));
		}

	}
	check(false);
	return FItemAddResult::AddedNone(FText::FromString("TryaddItem fallthrough error. GetOwner() check somehow failed."));
}

void UAC_Inventory::AddNewItem(UItemBase* Item, const int32 ItemAmountToAdd)
{
	UItemBase* NewItem;

	if (Item->bIsCopy || Item->bIsPickup)
	{
		//if the item is already a copy, or is a world pickup
		NewItem = Item;
		NewItem->ResetItemFlags();
	}
	else
	{
		//used when splitting or dragging to/from another inventory
		NewItem = Item->CreateItemCopy();
	}
	//set the inventory ref
	NewItem->OwningInventory = this;
	//set the Item quantity
	NewItem->SetQuantity(ItemAmountToAdd);

	//add new item to inventory
	InventoryContents.Add(NewItem);
	//adjust the inventory weight
	InventoryTotalWeight += NewItem->GetItemStackWeight();


	//update inventory widget.
	OnInventoryUpdated.Broadcast();

}
