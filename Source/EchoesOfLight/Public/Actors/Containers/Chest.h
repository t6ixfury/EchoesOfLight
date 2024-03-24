// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interface_Interaction.h"
#include "Enums/Enums.h"
#include "Chest.generated.h"


class UContainerBase;
class UBoxComponent;
class UWidgetComponent;
class UW_Interact;
class AMainCharacter;
class UAC_Inventory;
class UItemBase;
class UAudioComponent;

//---------------------------------------------------------------------------------------------------------------------------
//	STRUCTS AND ENUMS
//---------------------------------------------------------------------------------------------------------------------------

UENUM(BlueprintType)
enum class EContainerType : uint8
{
	Chest UMETA(DisplayName = "Chest"),
	Storage UMETA(DisplayName = "Storage"),
	Merchant UMETA(DisplayName = "Merchant")
};

USTRUCT(BlueprintType)
struct FChestItemData
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnywhere)
	FName DesiredItemId;

	UPROPERTY(EditAnywhere)
	int32 DesiredQuantiy;

	UPROPERTY(EditAnywhere)
	EItemType ItemType;
};

USTRUCT(BlueprintType)
struct FContainerAssetData
{
	GENERATED_USTRUCT_BODY()


	UPROPERTY(EditAnyWhere)
	TSubclassOf<UW_Interact> InteractWidgetClass;



};

USTRUCT(BlueprintType)
struct FContainerNumericData
{

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnyWhere)
	int32 TotalPossibleItem;

	UPROPERTY(EditAnyWhere)
		float Weight;
};




UCLASS()
class ECHOESOFLIGHT_API AChest : public AActor, public IInterface_Interaction
{
	GENERATED_BODY()



//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:


	DECLARE_MULTICAST_DELEGATE_OneParam(FChestOpenedDelegate, AChest*);
	FChestOpenedDelegate ChestOpenedDelegate;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
		EContainerType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
		FContainerAssetData AssetData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container")
		FContainerNumericData NumericData;

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(VisibleAnyWhere, Category = "Container | Item DataTables")
		UDataTable* ItemMundaneDataTable;


	UPROPERTY(VisibleAnyWhere, Category = "Container | Item DataTables")
		UDataTable* ItemConsumableDataTable;

	UPROPERTY(VisibleAnyWhere, Category = "Container | Item DataTables")
		UDataTable* ItemWeaponDataTable;

	UPROPERTY(VisibleAnyWhere, Category = "Container | Item DataTables")
		UDataTable* ItemArmorDataTable;

	UPROPERTY(VisibleAnyWhere, Category = "Container | Item DataTables")
		UDataTable* ItemQuestDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Variables")
		bool bIsChestOpen = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Variables")
		bool bIsChestLootable = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Container | Desired Items")
		TArray<FChestItemData> ItemsToAddToChest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation Variables")
		UAnimMontage* ChestOpen;

	UPROPERTY(VisibleAnywhere, Category = "Animation Variables")
		FTimerHandle TimerHandle_OpenChest;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
		UBoxComponent* AudioBox;


	

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------

public:	
	// Sets default values for this actor's properties
	AChest();

	void SetChestIsOpen();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Adds chest Items to the player inventory.
	virtual void Interact(AMainCharacter* PlayerCharacter) override;

	//Updates the interaction widget in HUD.
	void UpdateInteractableData();

	//Creates Item out of the chest.
	UItemBase* CreateItem(FChestItemData* ItemDataForCreation);

	// Finds the DataTables from the game files and sets them.
	void SetDataTables();


	void StopChestAudio();

	UFUNCTION()
	void PlayChestAmbientAudio( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void StopChestAmbientAudio(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
};
