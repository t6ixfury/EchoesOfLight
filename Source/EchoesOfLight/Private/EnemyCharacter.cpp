// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Structures/S_DamageInfo.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Structures/S_DamageInfo.h"
#include "Interfaces/Interface_Damagable.h"
#include "ActorComponents/AC_DamageSystem.h"

// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeTillDamagable = 0.25f;
	NormalAttackDamage = 10.f;

	DamageSystem = CreateDefaultSubobject<UAC_DamageSystem>(TEXT("Damage System"));
	CurrentDamageState = E_EnemyDamageStates::ApplyDamage;

	BaseAttackInfo.amount = NormalAttackDamage;
	BaseAttackInfo.bCanBeBlocked = true;
	BaseAttackInfo.DamageType = E_Damage_Type::Melee;
	BaseAttackInfo.DamageResponse = E_Damage_Response::None;

}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (DamageSystem)
	{
		if (DeathMontage)
		{
			DamageSystem->On_Death.AddDynamic(this, &AEnemyCharacter::Death);

		}
	}
	
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
	bool hasTakenDamage = false;
	if (DamageSystem && !DamageSystem->bisInvincible)
	{
		hasTakenDamage = DamageSystem->TakeDamage(DamageInfo);
		DamageSystem->bisInvincible = true;
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyCharacter::SetDamagable, TimeTillDamagable, false);
		

	}
	return hasTakenDamage;
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
		CapsuleTraceForEnemy();
	}
	return MontageDuration;
}


void AEnemyCharacter::Death_Implementation()
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* EnemyAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	if (EnemyAnimInstance)
	{
		EnemyAnimInstance->StopAllMontages(0.f);
		float MontageDuration = EnemyAnimInstance->Montage_Play(DeathMontage);

		GetWorldTimerManager().SetTimer(DeathTimer, this, &AEnemyCharacter::RemoveActor, MontageDuration, false);
	}
	
}

// *************** ENEMYAI INTERFACE IMPLEMENTATION (End) **************************//


void AEnemyCharacter::SetDamagable()
{
	if (DamageSystem)
	{
		DamageSystem->bisInvincible = false;
	}
}

void AEnemyCharacter::RemoveActor()
{
	this->K2_DestroyActor();
}

void AEnemyCharacter::CapsuleTraceForEnemy()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	UWorld* World = GetWorld();
	if (World)
	{
		float radius = 20.f;
		float halfHeight = 20.f;

		FHitResult HitResult;
		bool bHit = UKismetSystemLibrary::CapsuleTraceSingle(
			World,
			GetActorLocation(),
			GetActorLocation() + (GetActorForwardVector() * 200),
			radius,
			halfHeight,
			ETraceTypeQuery::TraceTypeQuery2,
			false,
			ActorsToIgnore,
			EDrawDebugTrace::ForDuration,
			HitResult,
			true,
			FLinearColor::Red, // Trace color
			FLinearColor::Green, // Hit color
			5.0f
		);

		UE_LOG(LogTemp, Warning, TEXT("BaseAttack from enemy has been called"))

			if (HitResult.GetActor())
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit Actor from enemy: %s"), *HitResult.GetActor()->GetName());
				IInterface_Damagable* HitActor = Cast<IInterface_Damagable>(HitResult.GetActor());

				if (HitActor)
				{
					HitActor->Execute_TakeIncomingDamage(HitResult.GetActor(), BaseAttackInfo);
					UE_LOG(LogTemp, Warning, TEXT("hit actor found enemy"))
				}

			}

	}
}


