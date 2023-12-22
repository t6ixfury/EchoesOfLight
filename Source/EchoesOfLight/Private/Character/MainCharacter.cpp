// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "EnemyCharacter.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Structures/S_DamageInfo.h"
#include "EnhancedInputComponent.h"
#include "InputAction.h"
#include "ActorComponents/AC_DamageSystem.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
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

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAction("Melee Attack",IE_Pressed, this, &AMainCharacter::MeleeAttack);
		UE_LOG(LogTemp, Warning, TEXT("Player input set"))

	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MeleeAttackIA, ETriggerEvent::Triggered, this, &AMainCharacter::MeleeAttack);

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

