// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enums/E_EnemyStates.h"
#include "Interfaces/Interface_Damagable.h"
#include "Interfaces/Interface_EnemyAi.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class ECHOESOFLIGHT_API AEnemyCharacter : public ACharacter, public IInterface_Damagable, public IInterface_EnemyAi
{
	GENERATED_BODY()

//For Variables
public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage State")
		E_EnemyDamageStates CurrentDamageState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		FTimerHandle DeathTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Timers")
		float TimeTillDamagable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damage properties")
		float NormalAttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Montages")
		class UAnimMontage* DeathMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Properites")
		FS_DamageInfo BaseAttackInfo;
		

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
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		float GetCurrentHealth();
		virtual float GetCurrentHealth_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		float GetMaxHealth();
		virtual float GetMaxHealth_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		void Heal(float amount);
		virtual void Heal_Implementation(float amount) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		bool TakeIncomingDamage(struct FS_DamageInfo DamageInfo);
		virtual bool TakeIncomingDamage_Implementation(struct FS_DamageInfo DamageInfo) override;



	/*
	ENEMYAI INTERFACE
	*/
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		float NormalAttack(class UAnimMontage* MontageToPlay);
		virtual float NormalAttack_Implementation(class UAnimMontage* MontageToPlay) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Damagable Interface Functions")
		void Death();
		virtual void Death_Implementation() override;


		UFUNCTION()
			void CapsuleTraceForEnemy();


private:

	//This function set the bisInvincible variable in damage system back to false;
	UFUNCTION()
		void SetDamagable();

	UFUNCTION()
		void RemoveActor();


};
