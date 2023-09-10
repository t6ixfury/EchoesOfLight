// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/Interface_Damagable.h"
#include "MainCharacter.generated.h"

UCLASS()
class ECHOESOFLIGHT_API AMainCharacter : public ACharacter, public IInterface_Damagable
{
	GENERATED_BODY()

// For Variables
public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_MainWidgetHandler* MainWidgetHandlerComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		float ClosestDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		 AEnemyCharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
		bool hasTargetEnemy;


// For Functions
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Combat")
		void ClosestEnemy(class AEnemyCharacter* enemyActor);

/*
	INTERFACES IMPLEMENTATION
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
};
