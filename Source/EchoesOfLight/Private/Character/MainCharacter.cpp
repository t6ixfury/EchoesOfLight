// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "EnemyCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Structures/S_DamageInfo.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"

// Sets default values
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

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)



 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClosestDistance = 100;
	hasTargetEnemy = false;

	TimeTillDamagable = 0.35f;

	//InventoryComponent = CreateDefaultSubobject<UAC_Inventory>(TEXT("Inventory"));
	MainWidgetHandlerComponent = CreateDefaultSubobject<UAC_MainWidgetHandler>(TEXT("Main Widget Handler"));
	DamageSystem = CreateDefaultSubobject<UAC_DamageSystem>(TEXT("Damage System"));


}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(inputMappingContext, 0);
		}
	}

	/*
	if (InventoryComponent)

	{
		UE_LOG(LogTemp, Warning, TEXT("Inventory components presence"));
	}
	*/
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//set up gameplay keybindings (Maybe delete later)
	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("Melee Attack",IE_Pressed, this, &AMainCharacter::MeleeAttack);
		PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMainCharacter::Jump);
		PlayerInputComponent->BindAction("Look", IE_Pressed, this, &AMainCharacter::Jump);

	}
	// Enhanced Input Logic
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MeleeAttackIA, ETriggerEvent::Triggered, this, &AMainCharacter::MeleeAttack);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Triggered, this, &AMainCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpIA, ETriggerEvent::Completed, this, &AMainCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveIA, ETriggerEvent::Triggered, this, &AMainCharacter::Move);

		EnhancedInputComponent->BindAction(LookIA, ETriggerEvent::Triggered, this, &AMainCharacter::Look);



		UE_LOG(LogTemp, Warning, TEXT("Enhanced input set"))
	}

}



void AMainCharacter::ClosestEnemy(AEnemyCharacter* enemyActor)
{
	float Distance = FVector::Dist(GetActorLocation(), enemyActor->GetActorLocation());

	if (Distance <= ClosestDistance)
	{
		TargetEnemy = enemyActor;
		hasTargetEnemy = true;
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

void AMainCharacter::MeleeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("Melee attack called."))
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* CharacterAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	float montageDuration = 0;

	float timeTillNextAttack = 0.5f;

	if (CharacterAnimInstance)
	{
		isAttacking = true;

		if (!isMontagePlaying && isWeaponEquipped)
		{
			switch (meleeAttackIndex)
			{
			case 0:
			{
				isMontagePlaying = true;

				montageDuration = CharacterAnimInstance->Montage_Play(baseDualMeleeAttack_1) - timeTillNextAttack;

				meleeAttackIndex=1;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;
			}
			case 1:
			{
				isMontagePlaying = true;

				montageDuration = CharacterAnimInstance->Montage_Play(baseDualMeleeAttack_2) - timeTillNextAttack;

				meleeAttackIndex=2;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;
			}
			case 2:
			{
				isMontagePlaying = true;

				montageDuration = CharacterAnimInstance->Montage_Play(baseDualMeleeAttack_3) - timeTillNextAttack;

				meleeAttackIndex=3;

				GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

				break;
			}
			case 3:
			{
				switch (meleeSpecialAttackIndex)
				{
				case 0:
				{
					isMontagePlaying = true;

					montageDuration = CharacterAnimInstance->Montage_Play(baseDualMeleeAttackSpecial_1) - timeTillNextAttack;

					meleeSpecialAttackIndex=1;

					meleeAttackIndex = 0;

					GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

					break;
				}
				case 1:
				{
					isMontagePlaying = true;

					montageDuration = CharacterAnimInstance->Montage_Play(baseDualMeleeAttackSpecial_1) - timeTillNextAttack;

					meleeSpecialAttackIndex=0;

					meleeAttackIndex = 0;

					GetWorldTimerManager().SetTimer(AttackTimer, this, &AMainCharacter::setIsMontagePlaying, montageDuration, false);

					break;
				}
				default:
					break;
				}
			}
			default:
				break;
			}
		}
	}


}




// *************** DAMAGABLE INTERFACE IMPLEMENTATION (BEGINNING) **************************//
float AMainCharacter::GetCurrentHealth_Implementation()
{
	if (DamageSystem)
	{
		return DamageSystem->Health;
	}
	return -1;
}

float AMainCharacter::GetMaxHealth_Implementation()
{
	if (DamageSystem)
	{
		return DamageSystem->MaxHealth;
	}

	return -1;
}

void AMainCharacter::Heal_Implementation(float amount)
{
	if (DamageSystem)
	{
		DamageSystem->Heal(amount);
	}
}

bool AMainCharacter::TakeIncomingDamage_Implementation(FS_DamageInfo DamageInfo)
{
	//UE_LOG(LogTemp, Warning, TEXT("Take Damage called main character."))
	bool hasTakenDamage = false;
	if (DamageSystem && !DamageSystem->bisInvincible)
	{
		hasTakenDamage = DamageSystem->TakeDamage(DamageInfo);
		DamageSystem->bisInvincible = true;
		GetWorldTimerManager().SetTimer(CanDamageTimer, this, &AMainCharacter::SetDamagable, TimeTillDamagable, false);


	}
	return hasTakenDamage;
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
}

// *************** DAMAGABLE INTERFACE IMPLEMENTATION (END) **************************//

