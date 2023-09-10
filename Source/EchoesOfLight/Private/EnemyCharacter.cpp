// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Structures/S_DamageInfo.h"
#include "ActorComponents/AC_DamageSystem.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSystem = CreateDefaultSubobject<UAC_DamageSystem>(TEXT("Damage System"));

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// *************** DAMAGABLE INTERFACE IMPLEMENTATION (BEGINNING) **************************//
float AEnemyCharacter::GetCurrentHealth_Implementation()
{
	if (DamageSystem)
	{
		return DamageSystem->Health;
	}
	return -1;
}

float AEnemyCharacter::GetMaxHealth_Implementation()
{
	if (DamageSystem)
	{
		return DamageSystem->MaxHealth;
	}

	return -1;
}

void AEnemyCharacter::Heal_Implementation(float amount)
{
	if (DamageSystem)
	{
		DamageSystem->Heal(amount);
	}
}

bool AEnemyCharacter::TakeIncomingDamage_Implementation(FS_DamageInfo DamageInfo)
{
	if (DamageSystem)
	{
		return DamageSystem->TakeDamage(DamageInfo);
	}
	return false;
}
// *************** DAMAGABLE INTERFACE IMPLEMENTATION (END) **************************//


// *************** ENEMYAI INTERFACE IMPLEMENTATION (BEGINNING) **************************//
float AEnemyCharacter::NormalAttack_Implementation(UAnimMontage* MontageToPlay)
{
	float MontageDuration = 0;
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* EnemyAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	if (EnemyAnimInstance)
	{
		MontageDuration = EnemyAnimInstance->Montage_Play(MontageToPlay);
	}
	return MontageDuration;
}

// *************** ENEMYAI INTERFACE IMPLEMENTATION (BEGINNING) **************************//
