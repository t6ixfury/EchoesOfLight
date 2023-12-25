// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Interfaces/Interface_Damagable.h"
#include "MainCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;
class UAC_CurrencySystem;
class UAC_ExperieceSystem;



DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=game)
class ECHOESOFLIGHT_API AMainCharacter : public ACharacter, public IInterface_Damagable
{
	GENERATED_BODY()

// For Variables
public:
	// Sets default values for this character's properties
	AMainCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_MainWidgetHandler* MainWidgetHandlerComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_DamageSystem* DamageSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_CurrencySystem* CurrencySystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		class UAC_ExperieceSystem* ExperienceSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		float ClosestDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		 AEnemyCharacter* TargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool hasTargetEnemy;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isAttacking = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isMontagePlaying = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		bool isWeaponEquipped = true;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		int32 meleeAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Combat")
		int32 meleeSpecialAttackIndex = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		FTimerHandle CanDamageTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Timers")
		float TimeTillDamagable;

	///montages////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* baseDualMeleeAttack_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* baseDualMeleeAttack_2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* baseDualMeleeAttack_3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* baseDualMeleeAttackSpecial_1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Montages")
		class UAnimMontage* baseDualMeleeAttackSpecial_2;





	/*
	INPUT ACTION MAPPINGS
	*/

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputMappingContext* inputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* MeleeAttackIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* JumpIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* LookIA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Inputs")
		class UInputAction* MoveIA;

	/*
	INPUT ACTION MAPPINGS

		END
	*/



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

	/*DamageInterface end*/


protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UFUNCTION()
		void MeleeAttack();



private:

	void SetDamagable();

	void setIsMontagePlaying();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* FollowCamera;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
