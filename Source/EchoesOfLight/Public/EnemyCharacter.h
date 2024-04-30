// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/E_EnemyStates.h"
#include "Interfaces/Interface_Damagable.h"
#include "Interfaces/Interface_EnemyAi.h"
#include "EnemyCharacter.generated.h"

class UEnemyHealthBar;
class UAC_DamageSystem;
class UWidgetComponent;

UCLASS()
class ECHOESOFLIGHT_API AEnemyCharacter : public ACharacter, public IInterface_Damagable, public IInterface_EnemyAi
{
	GENERATED_BODY()


//For Variables
public:
	// Sets default values for this character's properties
	AEnemyCharacter();
	//---------------------Components--------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UAC_DamageSystem* DamageSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		UWidgetComponent* HealthBar;

	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Components | Widget Classes")
		TSubclassOf<UEnemyHealthBar> HealthBarClass;

//--------------------------Variables--------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage State")
		E_EnemyDamageStates CurrentDamageState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle DeathTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle HitReactTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		float TimeTillDamagable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		float TimeTillHitReactAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Damage properties")
		float NormalAttackDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "EnemyProperties")
		float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitReactMontage")
		class UAnimMontage* HitReactMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* BaseAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		FS_DamageInfo BaseAttackInfo;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes")
		int32 level = 1;

	//animation checks

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
		bool bCanPlayhitReact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Checks")
		bool bIsIntialized = false;

//-------------------------DELEGATES------------------------------------------------------------

	DECLARE_DELEGATE(FOnEnemyHit);
	FOnEnemyHit OnHit;

	DECLARE_MULTICAST_DELEGATE_OneParam(FOnDeath, AEnemyCharacter*);
	FOnDeath OnDeath;





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


// For FUNCTIONS
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*
	DAMAGABLE INTERFACE
	*/
	UFUNCTION()
		virtual float GetCurrentHealth() override;

	UFUNCTION()
		virtual float GetMaxHealth() override;

	UFUNCTION()
		virtual void Heal(float amount) override;

	UFUNCTION()
		virtual bool TakeIncomingDamage(struct FS_DamageInfo DamageInfo) override;



	/*
	ENEMYAI INTERFACE
	*/

		virtual float NormalAttack() override;

	
		virtual void Death() override;

	
		virtual void SetMovementSpeed(float NewMaxSpeed) override;

		void UpdateStats();

protected:

	//trace for enemy attack. Calls the damagable interface on the hit actor.
	UFUNCTION()
		void CapsuleTraceForEnemy();


	//set state of the enemy character to death
	UFUNCTION()
		void SetDeath(AEnemyCharacter* enemy);

	//This function set the bisInvincible variable in damage system back to false;
	UFUNCTION()
		void SetDamagable();

	UFUNCTION()
		void RemoveActor();

	void CanPlayHitReactMontage();

	void SetEnemyWidgets();




};
