// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/E_DamageType.h"
#include "Enums/E_DamageResponse.h"
#include "Enums/E_DamageStates.h"
#include "Interfaces/Interface_Damagable.h"
#include "AC_DamageSystem.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ECHOESOFLIGHT_API UAC_DamageSystem : public UActorComponent
{
	GENERATED_BODY()

// For Variables
public:	
	// Sets default values for this component's properties
	UAC_DamageSystem();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Health;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float MaxHealth;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bisInvincible;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bisDead;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bisInterruptible;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bisBlocking;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCanBeParried;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		 E_Damage_State DamageState;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

//For Functions
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	float Heal(float amount);

	UFUNCTION(BlueprintCallable)
	bool TakeDamage(struct FS_DamageInfo DamageInfo);

private:
	E_Damage_State CanBeDamaged(bool shouldDamageInvincible, bool canBeBlocked);

	float SetHealth(float amount);



//Events

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlockedDamage, bool, Parryable);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoDamage);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Death);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOn_Damage_Response);


	// The event dispatcher instance
	UPROPERTY(BlueprintAssignable)
		FBlockedDamage BlockedDamage;

	UPROPERTY(BlueprintAssignable)
		FDoDamage DoDamage;

	UPROPERTY(BlueprintAssignable)
		FOn_Death On_Death;

	UPROPERTY(BlueprintAssignable)
		FOn_Damage_Response On_Damage_Response;
		
};
