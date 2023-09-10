// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/MainCharacter.h"
#include "EnemyCharacter.h"
#include "ActorComponents/AC_Inventory.h"
#include "ActorComponents/AC_MainWidgetHandler.h"
#include "Structures/S_DamageInfo.h"
#include "ActorComponents/AC_DamageSystem.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ClosestDistance = 100;
	hasTargetEnemy = false;

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

void AMainCharacter::ClosestEnemy(AEnemyCharacter* enemyActor)
{
	float Distance = FVector::Dist(GetActorLocation(), enemyActor->GetActorLocation());

	if (Distance <= ClosestDistance)
	{
		TargetEnemy = enemyActor;
		hasTargetEnemy = true;
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
	if (DamageSystem)
	{
		return DamageSystem->TakeDamage(DamageInfo);
	}
	return false;
}

// *************** DAMAGABLE INTERFACE IMPLEMENTATION (END) **************************//



// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

