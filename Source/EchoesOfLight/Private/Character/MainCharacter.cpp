// Fill out your copyright notice in the Description page of Project Settings.

//game
#include "Character/MainCharacter.h"
#include "EnemyCharacter.h"
#include "Structures/S_DamageInfo.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_CurrencySystem.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "ActorComponents/AC_ExperieceSystem.h"
#include "Widgets/HUD_MainCharacter.h"
#include "Actors/Items/Pickup.h"
#include "Widgets/W_EquipmentSlot.h"
#include "Widgets/W_EquipmentMenu.h"
#include "W_MainGUI.h"
#include "Actors/Items/ItemBase.h"
#include "ActorComponents/DialogueSystem.h"
#include "Save/Save_PlayerInfo.h"
#include "Save/EchoesGameInstance.h"
#include "EnemyCharacter.h"
#include "Managers/GameInfo.h"

//engine
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"


AMainCharacter::AMainCharacter()
{

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	BaseEyeHeight = 100.0f;


 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//combat variables
	ClosestDistance = 100;
	hasTargetEnemy = false;
	TimeTillDamagable = 0.35f;

	//Actor Components intialized
	MainWidgetHandlerComponent = CreateDefaultSubobject<UAC_MainWidgetHandler>(TEXT("Main Widget Handler"));
	DamageSystem = CreateDefaultSubobject<UAC_DamageSystem>(TEXT("Damage System"));
	CurrencySystem = CreateDefaultSubobject<UAC_CurrencySystem>(TEXT("Currenct System"));
	ExperienceSystem = CreateDefaultSubobject<UAC_ExperieceSystem>(TEXT("Experience System"));
	PlayerInventory = CreateDefaultSubobject<UAC_Inventory>(TEXT("Inventory System"));
	DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueSystem"));

	//Set the Weight and capacity of the Inventory.
	PlayerInventory->SetWeightCapacity(50.0f);
	PlayerInventory->SetSlotsCapacity(20);

	//Interaction
	InteractionCheckFrequency = 0.1;
	InteractionCheckDistance = 500.0f;

	//Save
	PlayerInfoSaveSlot = FString("PlayerInfoSlot1");

}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Set the player input mapping context.
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(inputMappingContext, 0);
		}
	}

	//sets health bar percantage to the 
	if (MainWidgetHandlerComponent->GUI)
	{
		float newHealth = DamageSystem->Health / DamageSystem->MaxHealth;
		MainWidgetHandlerComponent->GUI->SetHealthBarPercentage(newHealth);
	}

	BindEquipmentSlotDelegates();

	ExperienceSystem->ExperienceAddedDelegate.AddUObject(this, &AMainCharacter::ExperienceWasAdded);
	ExperienceSystem->LevelUpDelegate.AddUObject(this, &AMainCharacter::OnLevelUp);

	if (UEchoesGameInstance* instance = Cast<UEchoesGameInstance>(GetWorld()->GetGameInstance()))
	{
		LoadAll();
		UpdateAllWidgets();
		SaveAll();
		instance->GameInfo->SaveGameInfo(instance);
	}
}

void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// creates a delay on the line trace for looking at the Item to be performed at the rate set in InteractionCheckFrequency.
	if ((GetWorld()->TimeSince(InteractionData.LastInteractionCheckingTime) > InteractionCheckFrequency) && !DialogueSystem->bIsTalking)
	{
		PerformInteractionCheck();
	}
	GetCharacterMovementDirection();

	if (DamageSystem->Health <= 1)
	{
		if (!bIsDying)
		{
			bIsDying = true;
			Death();
		}
	}



}

void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Get the Enhanced Input component to set player actions.
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		InputComponent = EnhancedInputComponent;
		//Action for performing base attack
		EnhancedInputComponent->BindAction(MeleeAttackIA, ETriggerEvent::Triggered, this, &AMainCharacter::MeleeAttack);

		//Action to perform a Jump
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainCharacter::Move); 

		//Looking
		EnhancedInputComponent->BindAction(LookIA, ETriggerEvent::Triggered, this, &AMainCharacter::Look);

		//Action for toggle Inventory.
		EnhancedInputComponent->BindAction(InventoryIA, ETriggerEvent::Triggered, this, &AMainCharacter::ToggleInventory);

		//Action to pickup Items.
		EnhancedInputComponent->BindAction(InteractIA, ETriggerEvent::Completed, this, &AMainCharacter::BeginInteract);

		//Action to perform roll
		EnhancedInputComponent->BindAction(RollIA, ETriggerEvent::Triggered, this, &AMainCharacter::roll);

		//Action to equip weapon
		EnhancedInputComponent->BindAction(EuipWeaponIA, ETriggerEvent::Completed, this, &AMainCharacter::SpawnWeapon);

		//Action for toggle PauseMenu.
		EnhancedInputComponent->BindAction(PauseIA, ETriggerEvent::Completed, this, &AMainCharacter::TogglePause);
	}

}


void AMainCharacter::ClosestEnemy(AEnemyCharacter* enemyActor)
{
	//Calculate the distance between the charcter and the passed in enemyActor.
	float Distance = FVector::Dist(GetActorLocation(), enemyActor->GetActorLocation());

	// If the distance between the character and the passed in actor is less than closest distance.
	if (Distance <= ClosestDistance)
	{
		//Set Target enemy to that actor
		TargetEnemy = enemyActor;

		hasTargetEnemy = true;
	}
}

void AMainCharacter::UpdateInteractionWidget() const
{
	//make sure the item is still in the world
	if (IsValid(TargetInteractable.GetObject()))
	{
		//update Interaction widget.
		MainWidgetHandlerComponent->UpdateInteractionWidget(&TargetInteractable->InteractableData);
	}
}

void AMainCharacter::DropItem(UItemBase* ItemToDrop, const int32 QuantityToDrop)
{

	if (PlayerInventory->FindMatchingItem(ItemToDrop))
	{
		//spawning the drop items params
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.bNoFail = true;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		//location of spawn
		const FVector SpawnLocation{ GetActorLocation() + (GetActorForwardVector() * 50) };

		//transform of the spawned item.
		const FTransform SpawnTransform(GetActorRotation(), SpawnLocation);

		const int32 RemoveQuantity = PlayerInventory->RemoveAmountOfItem(ItemToDrop, QuantityToDrop);
		
		//spawned item
		APickup* Pickup = GetWorld()->SpawnActor<APickup>(APickup::StaticClass(), SpawnTransform, SpawnParams);

		//creates a reference to the pickup created.
		Pickup->InitializeDrop(ItemToDrop, RemoveQuantity);

		//remove Item from inventory
		PlayerInventory->RemoveSingleInstanceOfItem(ItemToDrop);

		//update inventory ui
		PlayerInventory->OnInventoryUpdated.Broadcast();
	}
}

void AMainCharacter::TogglePause()
{
	if (MainWidgetHandlerComponent)
	{
		MainWidgetHandlerComponent->TogglePauseMenu();
	}
	
}

void AMainCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AMainCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMainCharacter::SpawnWeapon()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->ItemReference == nullptr || 
		MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->ItemReference->ItemAssetData.DualSword == nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Null pointer from weapon slot."))
		return;
	}
	if (!isWeaponEquipped)
	{
		FName RightHandWeaponSlotName = TEXT("Weapon_RSocket");
		FName leftHandWeaponSlotName = TEXT("Weapon_LSocket");
		USkeletalMeshComponent* CharacterMesh = GetMesh();

		UWorld* World = GetWorld();
		if (World != nullptr)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			FVector RightSpawnLocation = CharacterMesh->GetSocketLocation(RightHandWeaponSlotName);
			FRotator RightSpawnRotation = CharacterMesh->GetSocketRotation(RightHandWeaponSlotName);
			FVector LeftSpawnLocation = CharacterMesh->GetSocketLocation(leftHandWeaponSlotName);
			FRotator LeftSpawnRotation = CharacterMesh->GetSocketRotation(leftHandWeaponSlotName);

			RightHandWeapon = World->SpawnActor<ABase_Sword>(MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->ItemReference->ItemAssetData.DualSword,
				RightSpawnLocation, RightSpawnRotation, SpawnParams);

			LeftHandWeapon = World->SpawnActor<ABase_Sword>(MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->ItemReference->ItemAssetData.DualSword,
				LeftSpawnLocation, LeftSpawnRotation, SpawnParams);
			
			UE_LOG(LogTemp, Warning, TEXT("Weapons are supposed to be spawned."))

			if (RightHandWeapon && LeftHandWeapon)
			{
				CurrentState = ECharacterState::Combat;
				CharacterStateChangeDelegate.Broadcast();

				LeftHandWeapon->BaseAttackInfo.Damage = LeftHandWeapon->BaseAttackInfo.Damage * (ExperienceSystem->CurrentLevel + LeftHandWeapon->BaseAttackInfo.AttackPower);
				RightHandWeapon->BaseAttackInfo.Damage = RightHandWeapon->BaseAttackInfo.Damage * (ExperienceSystem->CurrentLevel + RightHandWeapon->BaseAttackInfo.AttackPower);

				// Attach the weapon to the socket
				RightHandWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandWeaponSlotName);
				LeftHandWeapon->AttachToComponent(CharacterMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, leftHandWeaponSlotName);
				isWeaponEquipped = true;
				MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentStats();
				MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateStatProgressBars();
			}
		}
	} 
	else
	{
		DespawnWeapon();
	}
	

}

void AMainCharacter::DespawnWeapon()
{
	if (IsValid(RightHandWeapon) && IsValid(LeftHandWeapon))
	{
		CurrentState = ECharacterState::NonCombat;
		CharacterStateChangeDelegate.Broadcast();
		RightHandWeapon->Destroy();
		LeftHandWeapon->Destroy();
		RightHandWeapon = nullptr;
		LeftHandWeapon = nullptr;
		isWeaponEquipped = false;
	}
}


void AMainCharacter::OnDeathAnimationtimerEnd(AEnemyCharacter* Enemy)
{
	UE_LOG(LogTemp,Warning, TEXT("Death Called in character"))
	OnDeathAnimationEnd();
}

void AMainCharacter::OnWeaponEquipmentChange()
{
	//UE_LOG(LogTemp, Warning, TEXT("Weapon Broadcast fired."));
	if(isWeaponEquipped)
	{
		DespawnWeapon();
	}

	SpawnWeapon();


}

void AMainCharacter::BindEquipmentSlotDelegates()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot)
	{
		MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->WeaponChange.AddUObject(this, &AMainCharacter::OnWeaponEquipmentChange);
	}

	if(MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot)
	{
		MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->NetherBandChange.AddUObject(this, &AMainCharacter::NetherbandEquipped);
	}

	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot)
	{
		MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->AmuletChange.AddUObject(this, &AMainCharacter::AmuletEquipped);
	}
}

void AMainCharacter::OnWeaponSlotRemoval()
{
	DespawnWeapon();
	MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentWidget();
	
}

void AMainCharacter::NetherbandEquipped()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->ItemReference)
	{
		IncreaseStats(MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->ItemReference->ItemCharacerStatistics);
		MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentWidget();
	}
}

void AMainCharacter::NetherbandUnEquipped()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->ItemReference)
	{
		DecreaseStats(MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->ItemReference->ItemCharacerStatistics);
		MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentWidget();
	}
}

void AMainCharacter::AmuletEquipped()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->ItemReference)
	{
		FItemWeaponStatistics stats = MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->ItemReference->ItemWeaponStatistics;

		FS_DamageInfo addedWeaponStats;

		addedWeaponStats.AttackPower = stats.AttackPower;
		addedWeaponStats.AtttackSpeed = stats.AtttackSpeed;
		addedWeaponStats.CriticalHitRate = stats.CriticalHitRate;
		addedWeaponStats.MagicPower = stats.MagicPower;

		UpdateDualWeaponStats(addedWeaponStats, true);

		MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentWidget();


	}
}

void AMainCharacter::AmuletUnEquipped()
{
	if (MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->ItemReference)
	{
		FItemWeaponStatistics stats = MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->ItemReference->ItemWeaponStatistics;

		FS_DamageInfo addedWeaponStats;

		addedWeaponStats.AttackPower = stats.AttackPower;
		addedWeaponStats.AtttackSpeed = stats.AtttackSpeed;
		addedWeaponStats.CriticalHitRate = stats.CriticalHitRate;
		addedWeaponStats.MagicPower = stats.MagicPower;

		UpdateDualWeaponStats(addedWeaponStats, false);

		MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentWidget();

	}
}

void AMainCharacter::EquipEquipment(UItemBase* item)
{
	if (item)
	{
		switch (item->ItemType)
		{
		case EItemType::Amulet:
			if (MainWidgetHandlerComponent->EquipmentMenuWidget->Amulet_Slot->ItemReference)
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->RemoveAmulet();
				
			}
			else
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->AddAmulet(item);

			}
				break;
		case EItemType::Weapon:
			if (MainWidgetHandlerComponent->EquipmentMenuWidget->Weapon_Slot->ItemReference)
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->RemoveWeapon();
			}
			else
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->AddWeapon(item);
			}
			break;
		case EItemType::Netherband:

			if (MainWidgetHandlerComponent->EquipmentMenuWidget->Netherband_Slot->ItemReference)
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->RemoveNetherBand();
			}
			else
			{
				MainWidgetHandlerComponent->EquipmentMenuWidget->AddNetherBand(item);
			}
			break;
		
		default:
			break;
		}
	}
}

void AMainCharacter::UpdateDualWeaponStats(FS_DamageInfo stats, bool AddToStats)
{
	if (LeftHandWeapon && RightHandWeapon)
	{
		if (AddToStats)
		{
			//Lefthand weapon
			LeftHandWeapon->BaseAttackInfo.AttackPower =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.AttackPower + stats.AttackPower, 1, LeftHandWeapon->BaseAttackInfo.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.AtttackSpeed =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.AtttackSpeed + stats.AtttackSpeed, 1, LeftHandWeapon->BaseAttackInfo.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.CriticalHitRate =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.CriticalHitRate + stats.CriticalHitRate, 1, LeftHandWeapon->BaseAttackInfo.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.MagicPower =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.MagicPower + stats.MagicPower, 1, LeftHandWeapon->BaseAttackInfo.MaxStatValue);


			//righthand weapon
			RightHandWeapon->BaseAttackInfo.AttackPower =
				FMath::Clamp(RightHandWeapon->BaseAttackInfo.AttackPower + stats.AttackPower, 1, RightHandWeapon->BaseAttackInfo.MaxStatValue);

			RightHandWeapon->BaseAttackInfo.AtttackSpeed =
				FMath::Clamp(RightHandWeapon->BaseAttackInfo.AtttackSpeed + stats.AtttackSpeed, 1, RightHandWeapon->BaseAttackInfo.MaxStatValue);

			RightHandWeapon->BaseAttackInfo.CriticalHitRate =
				FMath::Clamp(RightHandWeapon->BaseAttackInfo.CriticalHitRate + stats.CriticalHitRate, 1, RightHandWeapon->BaseAttackInfo.MaxStatValue);

			RightHandWeapon->BaseAttackInfo.MagicPower =
				FMath::Clamp(RightHandWeapon->BaseAttackInfo.MagicPower + stats.MagicPower, 1, RightHandWeapon->BaseAttackInfo.MaxStatValue);


		
		}
		if (!AddToStats)
		{
			//Lefthand weapon
			LeftHandWeapon->BaseAttackInfo.AttackPower =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.AttackPower - stats.AttackPower, 1, MainCharacterStats.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.AtttackSpeed =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.AtttackSpeed - stats.AtttackSpeed, 1, MainCharacterStats.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.CriticalHitRate =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.CriticalHitRate - stats.CriticalHitRate, 1, MainCharacterStats.MaxStatValue);

			LeftHandWeapon->BaseAttackInfo.MagicPower =
				FMath::Clamp(LeftHandWeapon->BaseAttackInfo.MagicPower - stats.MagicPower, 1, MainCharacterStats.MaxStatValue);


			//righthand weapon
			RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.AttackPower =
				FMath::Clamp(RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.AttackPower - stats.AttackPower, 1, MainCharacterStats.MaxStatValue);

			RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.AtttackSpeed =
				FMath::Clamp(RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.AtttackSpeed - stats.AtttackSpeed, 1, MainCharacterStats.MaxStatValue);

			RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.CriticalHitRate =
				FMath::Clamp(RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.CriticalHitRate - stats.CriticalHitRate, 1, MainCharacterStats.MaxStatValue);

			RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.MagicPower =
				FMath::Clamp(RightHandWeapon->WeaponItemReference->ItemWeaponStatistics.MagicPower - stats.MagicPower, 1, MainCharacterStats.MaxStatValue);
		}


	}
}

void AMainCharacter::ExperienceWasAdded(float ExpAdded)
{
	if (MainWidgetHandlerComponent)
	{
		FString ExpMessage = FString::Printf(TEXT("EXP %d+"), static_cast<int32>(ExpAdded));
		MainWidgetHandlerComponent->ShowExperienceAlertWidget(FText::FromString(ExpMessage));
		UpdateAllWidgets();
	}
}

void AMainCharacter::OnLevelUp(int32 NewLevel)
{
	if (MainWidgetHandlerComponent)
	{

		DamageSystem->MaxHealth = DamageSystem->MaxHealth * static_cast<float>(MainCharacterStats.Constitution);

		DamageSystem->Health = DamageSystem->MaxHealth;

		Stamina = Stamina * static_cast<float>(MainCharacterStats.Stamina);

		CurrentStamina = Stamina;

		DamageSystem->DamageResistance = DamageSystem->DamageResistance * static_cast<float>(MainCharacterStats.DefensePower);


		FString ExpMessage = FString::Printf(TEXT("%d"), NewLevel);
		MainWidgetHandlerComponent->ShowLevelAlertWidget(FText::FromString(ExpMessage));
		UpdateAllWidgets();
	}
}

void AMainCharacter::DebugLevelUP()
{
	if (ExperienceSystem)
	{
		ExperienceSystem->LevelUp();
	}
}

void AMainCharacter::MeleeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack called."))
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* CharacterAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	float montageDuration = 0;

	float timeTillNextAttack = 0.5f;

	if (CharacterAnimInstance && !MainWidgetHandlerComponent->bIsMenuVisible && !DialogueSystem->bIsTalking)
	{
		isAttacking = true;

		if (!isMontagePlaying && isWeaponEquipped)
		{
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);

			switch (meleeAttackIndex)
			{
			case 0:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack1");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack1");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex=1;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				UE_LOG(LogTemp, Warning, TEXT("Attack1"))

				break;
			}
			case 1:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack2");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack2");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex=2;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				UE_LOG(LogTemp, Warning, TEXT("Attack2"))

				break;
			}
			case 2:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack3");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack3");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex=3;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				UE_LOG(LogTemp, Warning, TEXT("Attack3"))

				break;
			}
			case 3:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack4");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack4");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex = 4;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;

				UE_LOG(LogTemp, Warning, TEXT("Attack4"))
				
			}
			case 4:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack5");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack5");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex = 5;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;
				UE_LOG(LogTemp, Warning, TEXT("Attack5"))
			}
			case 5:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack6");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack6");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex = 6;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;
				UE_LOG(LogTemp, Warning, TEXT("Attack6"))
			}
			case 6:
			{
				isMontagePlaying = true;

				CharacterAnimInstance->Montage_Play(PrimaryAttack);
				CharacterAnimInstance->Montage_JumpToSection("Attack7");
				int32 SectionIndex = PrimaryAttack->GetSectionIndex("Attack7");
				montageDuration = PrimaryAttack->GetSectionLength(SectionIndex) - timeTillNextAttack;

				meleeAttackIndex = 0;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;

				UE_LOG(LogTemp, Warning, TEXT("Attack7"))
			}
			default:
				break;
			}
		}
	}


}

void AMainCharacter::ToggleInventory()
{
	MainWidgetHandlerComponent->ToggleEquipmentMenu();
}




// *************** DAMAGABLE INTERFACE IMPLEMENTATION (BEGINNING) **************************//




float AMainCharacter::GetCurrentHealth()
{
	if (DamageSystem)
	{
		return DamageSystem->Health;
	}
	return -1;
}

float AMainCharacter::GetMaxHealth()
{
	if (DamageSystem)
	{
		return DamageSystem->MaxHealth;
	}

	return -1;
}

void AMainCharacter::Heal(float amount)
{
	if (DamageSystem)
	{
		DamageSystem->Heal(amount);
	}
}

bool AMainCharacter::TakeIncomingDamage(FS_DamageInfo DamageInfo)
{

	// boolean to store the result wether damage was taken or not.
	bool hasTakenDamage = false;

	//DamageSystem is present and the character is not invincible.
	if (DamageSystem && !DamageSystem->bisInvincible)
	{
		// get the result of wether the player took damage or not.
		hasTakenDamage = DamageSystem->TakeDamage(DamageInfo);
		
		//set the player to be invincible till the candamagetimer is up then set it back to false.
		DamageSystem->bisInvincible = true;
		GetWorldTimerManager().SetTimer(CanDamageTimer, this, &AMainCharacter::SetDamagable, TimeTillDamagable, false);

		//sets health bar percantage to the 
		if (MainWidgetHandlerComponent->GUI)
		{
			float newHealth = DamageSystem->Health / DamageSystem->MaxHealth;
			MainWidgetHandlerComponent->GUI->SetHealthBarPercentage(newHealth);
		}

		UE_LOG(LogTemp, Warning, TEXT("take damage character."))

	}
	return hasTakenDamage;
}

void AMainCharacter::GetExpFromKill(AEnemyCharacter* enemy)
{
	if (enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("GetExpFromKill was called"))
		ExperienceSystem->AddExperience(enemy->BaseAttackInfo.Experience);
	}
}

void AMainCharacter::Death()
{
	if (DeathMonatage)
	{
		// Get the animation instance and play the death montage
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			// Play the death animation montage
			float time = AnimInstance->Montage_Play(DeathMonatage, 1.f);

			DamageSystem->bisDead = true;

				
			FTimerHandle deathtimer;
			GetWorld()->GetTimerManager().SetTimer(deathtimer, this, &AMainCharacter::OnDeathAnimationEnd, time, false);
		}

	}
}

void AMainCharacter::OnDeathAnimationEnd()
{
	UWorld* World = GetWorld();
	if (World)
	{
		FString CurrentLevelName = World->GetMapName();
		CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
		UGameplayStatics::OpenLevel(World, *CurrentLevelName);
	}
}

void AMainCharacter::SetDamagable()
{
	if (DamageSystem)
	{
		DamageSystem->bisInvincible = false;
	}
}

void AMainCharacter::setIsMontagePlaying()
{
	isMontagePlaying = false;
	isAttacking = false;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
	if (GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
	}

	
}


// *************** DAMAGABLE INTERFACE IMPLEMENTATION (END) **************************//

// *************** Interaction INTERFACE IMPLEMENTATION (BEGINNING) **************************//
void AMainCharacter::PerformInteractionCheck()
{
	// getting the time in seconds and setting variable
	InteractionData.LastInteractionCheckingTime = GetWorld()->GetTimeSeconds();

	//Gets the look location of the third person character.
	FVector TraceStart{ GetPawnViewLocation() };
	// Gets the view rotation vector and multiplies it by the desired check distance
	FVector TraceEnd{ TraceStart + (GetViewRotation().Vector() * InteractionCheckDistance) };

	//make sure the actor is looking at the object and not behind it.
	float LookDirection = FVector::DotProduct(GetActorForwardVector(),GetViewRotation().Vector());

	if (LookDirection > 0)
	{
		//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 1.0f, 0, 2.0f);

		FCollisionQueryParams QueryParams;

		QueryParams.AddIgnoredActor(this);

		FHitResult TraceHit;

		// if the trace hits an item
		if (GetWorld()->LineTraceSingleByChannel(TraceHit, TraceStart, TraceEnd, ECC_Visibility, QueryParams))
		{
			//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Blue, true);
			//TODO: Trace hit enemy actor and crashed the game.
			//checks to see the object we are looking at is implementing the interaction interface
			if (TraceHit.GetActor()->GetClass()->ImplementsInterface(UInterface_Interaction::StaticClass()))
			{

				//this make sure that we will not interact with an item outside a specific bound. InteractionCheckDistance in this case.
				if (TraceHit.GetActor() != InteractionData.CurrentInteractable)
				{
					//UE_LOG(LogTemp, Warning, TEXT("Hit actor found"))
					FoundInteractable(TraceHit.GetActor());
					return;
				}
				//checks if we are still looking at the same interactable item and not to run anything. 
				if (TraceHit.GetActor() == InteractionData.CurrentInteractable)
				{
					return;
				}

			}
		}
	}

	
	//called if not object is found on the trace
	NoInteractableFound();
}

void AMainCharacter::FoundInteractable(AActor* NewInteractable)
{
	//checks if we found a new interactable while interacting with a timed object which will end the interact sequence
	if (IsInteracting())
	{
		EndInteract();
	}
	//Removes the focus from the last interactable we interacted with
	if (InteractionData.CurrentInteractable)
	{
		TargetInteractable = InteractionData.CurrentInteractable;

		TargetInteractable->EndFocus();
	}

	InteractionData.CurrentInteractable = NewInteractable;
	TargetInteractable = NewInteractable;

	//this will show the interaction widget on screen and update it simultaneously
	MainWidgetHandlerComponent->UpdateInteractionWidget(&TargetInteractable->InteractableData);

	TargetInteractable->BeginFocus();

}

void AMainCharacter::NoInteractableFound()
{
	if (IsInteracting())
	{
		//clear interaction timer
		GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);
	}
	if (InteractionData.CurrentInteractable)
	{
		//this make sure the interactable is still in the world and not destroyed before it calls end focus so it will stop it calling the function when there is not an object
		if (IsValid(TargetInteractable.GetObject()))
		{
			TargetInteractable->EndFocus();
		}

		MainWidgetHandlerComponent->HideInteractionWidget();

		//reset currentinteractable and target interactable to null
		InteractionData.CurrentInteractable = nullptr;
		TargetInteractable = nullptr;
	}
}

void AMainCharacter::BeginInteract()
{
	//Verify nothing has changed with the interaction state since beginning of interaction.
	PerformInteractionCheck();

	if (InteractionData.CurrentInteractable)
	{
		//this make sure the interactable is still in the world and not destroyed before it calls end focus so it will stop it calling the function when there is not an object
		if (IsValid(TargetInteractable.GetObject()))
		{
			//calls the items Begin iteract function
			TargetInteractable->BeginInteract();
			
			//use to create timed interaction. Current set to happen in 0.1 seconds.
			if (FMath::IsNearlyZero(TargetInteractable->InteractableData.InteractionDuration, 0.1f))
			{
				Interact();
			}
			else
			{
				//use to set timer for interaction delay
				GetWorldTimerManager().SetTimer(TimerHandle_Interaction, this, &AMainCharacter::Interact, TargetInteractable->InteractableData.InteractionDuration, false);
			}
		}
	}
}

void AMainCharacter::EndInteract()
{
	//clear timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	//if the item is still in the world
	if (IsValid(TargetInteractable.GetObject()))
	{
		//in item, call endInteract.
		TargetInteractable->EndInteract();
	}

}

void AMainCharacter::Interact()
{
	//clear timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Interaction);

	//if the item is still in the world
	if (IsValid(TargetInteractable.GetObject()))
	{
		//in item, call Interact and pass a ref of maincharacter.
		TargetInteractable->Interact(this);
	}
}

// *************** Interaction INTERFACE IMPLEMENTATION (END) **************************//


void AMainCharacter::GetCharacterMovementDirection()
{
	FVector Velocity = GetVelocity();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();

	// Define custom thresholds
	const float ForwardBackwardThreshold = 0.5f; // example value, adjust as needed
	const float RightLeftThreshold = 0.5f; // example value, adjust as needed

	if (Velocity.SizeSquared() < KINDA_SMALL_NUMBER * KINDA_SMALL_NUMBER)
	{
		MovementDirection = EMovementDirection::Stationary;
		return;
	}

	FVector NormalizedVelocity = Velocity.GetSafeNormal();

	float ForwardDot = FVector::DotProduct(NormalizedVelocity, ForwardVector);
	float RightDot = FVector::DotProduct(NormalizedVelocity, RightVector);

	// Diagonal Movement
	bool bIsMovingForward = ForwardDot > ForwardBackwardThreshold;
	bool bIsMovingBackward = ForwardDot < -ForwardBackwardThreshold;
	bool bIsMovingRight = RightDot > RightLeftThreshold;
	bool bIsMovingLeft = RightDot < -RightLeftThreshold;

	//character is moving forward and to the right at the same time.
	if (bIsMovingForward && bIsMovingRight)
	{
		MovementDirection = EMovementDirection::Forward;
		return;
	}
	//character is moving forward and to the left at the same time.
	if (bIsMovingForward && bIsMovingLeft)
	{
		MovementDirection = EMovementDirection::Forward;
		return;
	}
	//character is moving backward and to the right at the same time.
	if (bIsMovingBackward && bIsMovingRight)
	{
		MovementDirection = EMovementDirection::Backward;
		return;
	}
	//character is moving backward and to the left at the same time.
	if (bIsMovingBackward && bIsMovingLeft)
	{
		MovementDirection = EMovementDirection::Backward;
		return;
	}

	// Straight Movement
	if (bIsMovingForward)
	{
		MovementDirection = EMovementDirection::Forward;
		return;
	}
	if (bIsMovingBackward)
	{
		MovementDirection = EMovementDirection::Backward;
		return;
	}
	if (bIsMovingRight)
	{
		MovementDirection = EMovementDirection::Right;
		return;
	}
	if (bIsMovingLeft)
	{
		MovementDirection = EMovementDirection::Left;
		return;
	}
}


void AMainCharacter::roll()
{

	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* CharacterAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;
	float montageDuration = 0;

	int32 SectionIndex = 0;

	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);

	if (CharacterAnimInstance && !isMontagePlaying && !DialogueSystem->bIsTalking)
	{
		switch (MovementDirection)
		{
		case EMovementDirection::Forward:
			isMontagePlaying = true;

			CharacterAnimInstance->Montage_Play(RollMontage);
			CharacterAnimInstance->Montage_JumpToSection("Roll_Forward");
			SectionIndex = RollMontage->GetSectionIndex("Roll_Forward");
			montageDuration = RollMontage->GetSectionLength(SectionIndex);
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);
			//UE_LOG(LogTemp, Warning, TEXT("Forward Roll"))
			break;
		case EMovementDirection::Backward:
			isMontagePlaying = true;

			CharacterAnimInstance->Montage_Play(RollMontage);
			CharacterAnimInstance->Montage_JumpToSection("Roll_Backward");
			SectionIndex = RollMontage->GetSectionIndex("Roll_Backward");
			montageDuration = RollMontage->GetSectionLength(SectionIndex);
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);
		//	UE_LOG(LogTemp, Warning, TEXT("Backward Roll"))
			break;
		case EMovementDirection::Right:
			isMontagePlaying = true;

			CharacterAnimInstance->Montage_Play(RollMontage);
			CharacterAnimInstance->Montage_JumpToSection("Roll_Right");
			SectionIndex = RollMontage->GetSectionIndex("Roll_Right");
			montageDuration = RollMontage->GetSectionLength(SectionIndex);
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);
			//UE_LOG(LogTemp, Warning, TEXT("Right Roll"))
			break;
		case EMovementDirection::Left:
			isMontagePlaying = true;

			CharacterAnimInstance->Montage_Play(RollMontage);
			CharacterAnimInstance->Montage_JumpToSection("Roll_Left");
			SectionIndex = RollMontage->GetSectionIndex("Roll_Left");
			montageDuration = RollMontage->GetSectionLength(SectionIndex);
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);
			UE_LOG(LogTemp, Warning, TEXT("Left Roll"))
			break;
		case EMovementDirection::Stationary:
			isMontagePlaying = true;

			CharacterAnimInstance->Montage_Play(RollMontage);
			CharacterAnimInstance->Montage_JumpToSection("Roll_Forward");
			SectionIndex = RollMontage->GetSectionIndex("Roll_Forward");
			montageDuration = RollMontage->GetSectionLength(SectionIndex);
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);
			//UE_LOG(LogTemp, Warning, TEXT("Stationary Roll"))
			break;
		default:
			break;
		}
	}
}

//----------------------------Widgets-------------------------------------------------

void AMainCharacter::UpdateAllWidgets()
{
	UE_LOG(LogTemp,Warning, TEXT("UpdateWidget"))
	//sets health bar percantage to the 
	if (MainWidgetHandlerComponent->GUI)
	{
		float newHealth = DamageSystem->Health / DamageSystem->MaxHealth;
		MainWidgetHandlerComponent->GUI->SetHealthBarPercentage(newHealth);

		float StaminaPercentage = CurrentStamina / Stamina;
		MainWidgetHandlerComponent->GUI->SetStaminaBarPercetage(StaminaPercentage);

		float ExperiencePercentage = ExperienceSystem->ExpGainedForNewLevel / ExperienceSystem->NeededExp;
		MainWidgetHandlerComponent->GUI->SetExperienceBarPercentage(ExperiencePercentage);
		//float ExperiencePercentage = ExperienceSystem->CurrentExp - ExperienceSystem->Levels.LevelToExperience[ExperienceSystem->ExpToNextLevel - 1] / (ExperienceSystem->ExpToNextLevel - ExperienceSystem->CurrentExp);
		MainWidgetHandlerComponent->GUI->SetLevelText(FText::AsNumber(ExperienceSystem->CurrentLevel));
	}

	MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateEquipmentStats();
	MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateCharacterStats();
	MainWidgetHandlerComponent->EquipmentMenuWidget->UpdateStatProgressBars();

}


//----------------------------Stats-------------------------------------------------



void AMainCharacter::IncreaseStats(FItemCharacerStatistics Stats)
{
	MainCharacterStats.Strength = FMath::Clamp(MainCharacterStats.Strength + Stats.Strength, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.Stamina = FMath::Clamp(MainCharacterStats.Stamina + Stats.Stamina, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.DefensePower = FMath::Clamp(MainCharacterStats.DefensePower + Stats.Defense, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.Constitution = FMath::Clamp(MainCharacterStats.Constitution + Stats.Health, 1, MainCharacterStats.MaxStatValue);

}

void AMainCharacter::DecreaseStats(FItemCharacerStatistics Stats)
{
	MainCharacterStats.Strength = FMath::Clamp(MainCharacterStats.Strength - Stats.Strength, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.Stamina = FMath::Clamp(MainCharacterStats.Stamina - Stats.Stamina, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.DefensePower = FMath::Clamp(MainCharacterStats.DefensePower - Stats.Defense, 1, MainCharacterStats.MaxStatValue);

	MainCharacterStats.Constitution = FMath::Clamp(MainCharacterStats.Constitution - Stats.Health, 1, MainCharacterStats.MaxStatValue);

}


void AMainCharacter::SavePlayerInfo()
{
	if (UWorld* World = GetOwner()->GetWorld())
	{
		UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(World->GetGameInstance());

		if (IsValid(GameInstance))
		{
			if (USave_PlayerInfo* Save = Cast<USave_PlayerInfo>(UGameplayStatics::CreateSaveGameObject(USave_PlayerInfo::StaticClass())))
			{
				Save->sHealth = DamageSystem->Health;
				Save->sStatsLevels = MainCharacterStats;

				if (LeftHandWeapon)
				{
					Save->sCurrentWeapnStats.AttackPower = LeftHandWeapon->BaseAttackInfo.AttackPower;
					Save->sCurrentWeapnStats.AtttackSpeed = LeftHandWeapon->BaseAttackInfo.AtttackSpeed;
					Save->sCurrentWeapnStats.CriticalHitRate = LeftHandWeapon->BaseAttackInfo.CriticalHitRate;
					Save->sCurrentWeapnStats.MagicPower = LeftHandWeapon->BaseAttackInfo.MagicPower;
					Save->sCurrentWeapnStats.Damage = LeftHandWeapon->BaseAttackInfo.Damage;
				}

				UGameplayStatics::SaveGameToSlot(Save, GameInstance->PlayerInfoSlot, 0);
			//UE_LOG(LogTemp, Warning, TEXT("PlayerInfo Saved"));
			}
			
		}

	}

}

void AMainCharacter::LoadPlayerInfo()
{
	if (UWorld* World = GetOwner()->GetWorld())
	{
		UEchoesGameInstance* GameInstance = Cast<UEchoesGameInstance>(World->GetGameInstance());

		if (UGameplayStatics::DoesSaveGameExist(GameInstance->PlayerInfoSlot, 0))
		{
			//SetActorTransform(GameInstance->PlayerInfoData->sPlayerTransform);

			//SetActorRotation(GameInstance->PlayerInfoData->sPlayerRotation);

			

			GameInstance->PlayerInfoData = Cast<USave_PlayerInfo>(UGameplayStatics::LoadGameFromSlot(GameInstance->PlayerInfoSlot, 0));

			MainCharacterStats = GameInstance->PlayerInfoData->sStatsLevels;

			DamageSystem->Health = GameInstance->PlayerInfoData->sHealth;

			if (LeftHandWeapon && RightHandWeapon)
			{
				LeftHandWeapon->BaseAttackInfo.AttackPower = GameInstance->PlayerInfoData->sCurrentWeapnStats.AttackPower;
				LeftHandWeapon->BaseAttackInfo.AtttackSpeed = GameInstance->PlayerInfoData->sCurrentWeapnStats.AtttackSpeed;
				LeftHandWeapon->BaseAttackInfo.CriticalHitRate = GameInstance->PlayerInfoData->sCurrentWeapnStats.CriticalHitRate;
				LeftHandWeapon->BaseAttackInfo.MagicPower = GameInstance->PlayerInfoData->sCurrentWeapnStats.MagicPower;
				LeftHandWeapon->BaseAttackInfo.Damage = GameInstance->PlayerInfoData->sCurrentWeapnStats.Damage;

				RightHandWeapon->BaseAttackInfo.AttackPower = GameInstance->PlayerInfoData->sCurrentWeapnStats.AttackPower;
				RightHandWeapon->BaseAttackInfo.AtttackSpeed = GameInstance->PlayerInfoData->sCurrentWeapnStats.AtttackSpeed;
				RightHandWeapon->BaseAttackInfo.CriticalHitRate = GameInstance->PlayerInfoData->sCurrentWeapnStats.CriticalHitRate;
				RightHandWeapon->BaseAttackInfo.MagicPower = GameInstance->PlayerInfoData->sCurrentWeapnStats.MagicPower;
				RightHandWeapon->BaseAttackInfo.Damage = GameInstance->PlayerInfoData->sCurrentWeapnStats.Damage;
			}
			//UE_LOG(LogTemp, Warning, TEXT("PlayerInfo Loaded"));
			UpdateAllWidgets();
		}
	}

}

void AMainCharacter::LoadAll()
{
	LoadPlayerInfo();
	ExperienceSystem->LoadExperience();
	PlayerInventory->LoadInventory();
	MainWidgetHandlerComponent->EquipmentMenuWidget->LoadEquipmentSlots();
	//UE_LOG(LogTemp, Warning, TEXT("load all called"));
}

void AMainCharacter::SaveAll()
{
	SavePlayerInfo();
	ExperienceSystem->SaveExperience();
	PlayerInventory->SaveInventory();
	MainWidgetHandlerComponent->EquipmentMenuWidget->SaveEquipment();

	//UE_LOG(LogTemp, Warning, TEXT("Save all called"));
}
