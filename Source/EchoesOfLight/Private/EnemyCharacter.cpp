// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AI/Controllers/EnemyBaseController.h"
#include "Structures/S_DamageInfo.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Structures/S_DamageInfo.h"
#include "Interfaces/Interface_Damagable.h"
#include "ActorComponents/AC_DamageSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TimeTillDamagable = 0.25f;
	NormalAttackDamage = 10.f;
	TimeTillHitReactAction = 1.5f;
	bCanPlayhitReact = true;

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
			DamageSystem->On_Death.AddDynamic(this, &AEnemyCharacter::SetDeath);

		}
	}
	
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovementSpeed = GetVelocity().Size();

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// *************** DAMAGABLE INTERFACE IMPLEMENTATION (BEGINNING) **************************//

//Returns the current health on the main character.
float AEnemyCharacter::GetCurrentHealth_Implementation()
{
	if (DamageSystem)
	{
		return DamageSystem->Health;
	}
	return -1;
}

//Returns the max health of the main character
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

	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* EnemyAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	if (DamageSystem && !DamageSystem->bisInvincible)
	{
		if (EnemyAnimInstance && bCanPlayhitReact)
		{
			float MontageDuration = EnemyAnimInstance->Montage_Play(HitReactMontage);
			bCanPlayhitReact = false;
			GetWorldTimerManager().SetTimer(HitReactTimer, this, &AEnemyCharacter::CanPlayHitReactMontage, TimeTillHitReactAction, false);
			OnHit.ExecuteIfBound();
		}
		hasTakenDamage = DamageSystem->TakeDamage(DamageInfo);
		DamageSystem->bisInvincible = true;
		GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemyCharacter::SetDamagable, TimeTillDamagable, false);
	}
	return hasTakenDamage;
}

// *************** DAMAGABLE INTERFACE IMPLEMENTATION (END) **************************//


// *************** ENEMYAI INTERFACE IMPLEMENTATION (BEGINNING) **************************//
float AEnemyCharacter::NormalAttack()
{
	float MontageDuration = 0;
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* EnemyAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;

	if (EnemyAnimInstance)
	{
		MontageDuration = EnemyAnimInstance->Montage_Play(BaseAttack);
		CapsuleTraceForEnemy();
	}
	return MontageDuration;
}


void AEnemyCharacter::Death()
{
	UE_LOG(LogTemp, Warning, TEXT("DeathImplementation Called"))
	USkeletalMeshComponent* MeshComp = GetMesh();
	UAnimInstance* EnemyAnimInstance = MeshComp ? MeshComp->GetAnimInstance() : nullptr;


	if (EnemyAnimInstance && DeathMontage)
	{
		EnemyAnimInstance->StopAllMontages(0);
		float MontageDuration = EnemyAnimInstance->Montage_Play(DeathMontage) -  0.5f;

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
	if (DamageSystem)
	{
		DamageSystem->bisDead = true;
	}
	this->K2_DestroyActor();
}

void AEnemyCharacter::CanPlayHitReactMontage()
{
	bCanPlayhitReact = true;
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
			EDrawDebugTrace::Persistent,
			HitResult,
			true,
			FLinearColor::Red, 
			FLinearColor::Green,
			5.0f
		);

			if (HitResult.GetActor())
			{
				IInterface_Damagable* HitActor = Cast<IInterface_Damagable>(HitResult.GetActor());

				if (HitActor)
				{
					HitActor->Execute_TakeIncomingDamage(HitResult.GetActor(), BaseAttackInfo);
				}

			}

	}
}

void AEnemyCharacter::SetDeath()
{
	AEnemyBaseController* AIController = Cast<AEnemyBaseController>(this->GetController());

	if (AIController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController called"))
			AIController->SetStateAsDeath();
	}
}

void AEnemyCharacter::SetMovementSpeed(float NewMaxSpeed)
{
	GetCharacterMovement()->MaxWalkSpeed = NewMaxSpeed;

}


