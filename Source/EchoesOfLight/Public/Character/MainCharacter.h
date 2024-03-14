// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/Interface_Damagable.h"
#include "Interfaces/Interface_Interaction.h"
#include "Structures/Structs.h"
#include "MainCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAC_CurrencySystem;
class UAC_ExperieceSystem;
class AHUD_MainCharacter;
class UItemBase;

UENUM()
enum class EMovementDirection : uint8
{
	Forward UMETA(DisplayName = "Forward"),
	Backward UMETA(DisplayName = "Backward"),
	Right UMETA(DisplayName = "Right"),
	Left UMETA(DisplayName = "Left"),
	Stationary UMETA(DisplayName = "Stationary")

};

USTRUCT()
struct FCharacterStats
{
	GENERATED_USTRUCT_BODY()

public:

	int32 Stamina = 10;

	int32 Strength = 10;
	
	int32 DefensePower = 10;

	int32 Constitution = 10;

	int32 MaxStatValue = 99;


};

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_MULTICAST_DELEGATE(FWeaponEquippedDelegate)

UCLASS(config=game)
class ECHOESOFLIGHT_API AMainCharacter : public ACharacter, public IInterface_Damagable
{
	GENERATED_BODY()

//---------------------------------------------------------------------------------------------------------------------------
//	PROPERTIES AND VARIABLES
//---------------------------------------------------------------------------------------------------------------------------

public:
	UPROPERTY()
		AHUD_MainCharacter* HUD;

//------------------------------Components--------------------------------------------------------------------------

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_MainWidgetHandler* MainWidgetHandlerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_CurrencySystem* CurrencySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_ExperieceSystem* ExperienceSystem;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UAC_Inventory* PlayerInventory;

private:

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

//------------------------------Combat Variables--------------------------------------------------------------------------
public:

		FCharacterStats MainCharacterStats;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		float ClosestDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		 AEnemyCharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool hasTargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isMontagePlaying = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isWeaponEquipped = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		int32 meleeAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		int32 meleeSpecialAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		FTimerHandle CanDamageTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		float TimeTillDamagable;

//------------------------------Equipment--------------------------------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment | Weapon")
		ABase_Sword* LeftHandWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Equipment | Weapon")
		ABase_Sword* RightHandWeapon;

	UPROPERTY(EditAnywhere, Category = "Equipment | Weapon")
		TSubclassOf<ABase_Sword> DualSwordWeaponClass;


//------------------------------Montages--------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* PrimaryAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* RollMontage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement")
		EMovementDirection MovementDirection;




//------------------------------Interaction Variables--------------------------------------------------------------------------

	/// <Start>
	UPROPERTY(VisibleAnywhere, Category = "Interact")
	TScriptInterface<IInterface_Interaction> TargetInteractable;

	UPROPERTY(VisibleAnywhere, Category = "Interact")
	float InteractionCheckFrequency;

	UPROPERTY(VisibleAnywhere, Category = "Interact")
	float InteractionCheckDistance;

	UPROPERTY(VisibleAnywhere, Category = "Interact")
	FTimerHandle TimerHandle_Interaction;

	UPROPERTY(VisibleAnywhere, Category = "Interact")
	FInteractionData InteractionData;



//------------------------------INPUT ACTION MAPPINGS--------------------------------------------------------------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputMappingContext* inputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* MeleeAttackIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* JumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* LookIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* MoveIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* InventoryIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* InteractIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* RollIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* EuipWeaponIA;

//---------------------------------------------------------------------------------------------------------------------------
//	FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------




//------------------------------Engine Functions--------------------------------------------------------------------------
public:
	// Sets default values for this character's properties
	AMainCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


//------------------------------Combat Functions--------------------------------------------------------------------------

public:
	// Calculates the distance from the passed in enemy actor and if the distance is the closest to the actor it set hasTargetEnemy to true;
	UFUNCTION(BlueprintCallable, Category = "Combat")
		void ClosestEnemy(class AEnemyCharacter* enemyActor);

	//Damagable interface

	//Returns the current health of a player
	UFUNCTION( Category = "Damagable Interface Functions")
	virtual float GetCurrentHealth() override;

	//Returns the Max Health of the player.
	UFUNCTION( Category = "Damagable Interface Functions")
	virtual float GetMaxHealth() override;

	//Heals player by the amount passed in.
	UFUNCTION( Category = "Damagable Interface Functions")
	virtual void Heal(float amount) override;

	//Handles the incoming damage of an enemy
	UFUNCTION( Category = "Damagable Interface Functions")
	virtual bool TakeIncomingDamage(struct FS_DamageInfo DamageInfo) override;


//------------------------------Equipment system functions--------------------------------------------------------------------------
	UFUNCTION()
	// Function to be called on the weapon change delegate in the equipment slot widget.
	void OnWeaponEquipmentChange();

	//Binds all necessary delegate to the perspective function for the Equipment slot widget.
	void BindEquipmentSlotDelegates();

	//Despawns Weapon and Update Equipment menu widget
	void OnWeaponSlotRemoval();

	void NetherbandEquipped(UItemBase* NetherbandItem);

	void NetherbandUnEquipped(UItemBase* NetherbandItem);


protected:
	//Performs the basic attack of the character.
	UFUNCTION()
		void MeleeAttack();

private:

	//This Function changes the characters damage system variable bIsvincible to false; (change this)
	UFUNCTION()
	void SetDamagable();

	//This Function set isMontagePlaying to false (change this)
	UFUNCTION()
	void setIsMontagePlaying();

	//Gets the current direction the character is moving towards and set the Movement Direction Variable.
	UFUNCTION()
	void GetCharacterMovementDirection();

	UFUNCTION()
	void roll();


//------------------------------Interaction Functions--------------------------------------------------------------------------
public:


	UFUNCTION()
	//Updates HUD Interaction widget.
	void UpdateInteractionWidget() const;

	//Interface

	//Performs a line trace to see if an item is in our view and what to do if there is.
	UFUNCTION()
		void PerformInteractionCheck();

	//Resets TargetInteractable to the new interactable we are looking at if it is differents. The updates interaction widget and set focus.
	UFUNCTION()
		void FoundInteractable(AActor* NewInteractable);
	
	//Clears the interaction timer and Removes focus from last interaction and updates the UI and hides the Interaction widget.
	UFUNCTION()
		void NoInteractableFound();

	//Make sure the item found has not changed and start interaction timer.
	UFUNCTION()
		void BeginInteract();

	//clears the interaction timer and calls endInteract on the item.
	UFUNCTION()
		void EndInteract();

	//clears the interaction timer and calls Interact on the item.
	UFUNCTION()
		void Interact();


//------------------------------Inventory Functions--------------------------------------------------------------------------
public:

	//Drops Item from Inventory
	UFUNCTION()
		void DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop);

protected:
	//Brings Up the Inventory ui
	UFUNCTION()
		void ToggleInventory();


protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

//------------------------------Equipment Functions--------------------------------------------------------------------------
public:
	void SpawnWeapon();

	void DespawnWeapon();

//------------------------------Character Variable functions--------------------------------------------------------------------------

public:
	//Updates all variables from the character to the proper widget
	void UpdateAllWidgets();

	void IncreaseStats(FItemCharacerStatistics Stats);

	void DecreaseStats(FItemCharacerStatistics Stats);
//------------------------------INLINE Functions--------------------------------------------------------------------------

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	
	//Returns true if Character is still interacting with the same item.
	FORCEINLINE bool IsInteracting() const { return GetWorldTimerManager().IsTimerActive(TimerHandle_Interaction);};

	// Returns the Characters Inventory.
	FORCEINLINE UAC_Inventory* GetInventory() const { return PlayerInventory; };
};
